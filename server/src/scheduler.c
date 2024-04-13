/***************************************************************************//**
 *
 * @file scheduler.c
 * @brief This code involves scheduler function definitions
 * Created on: Feb 15, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 6,8
 *
 ******************************************************************************/

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "scheduler.h"
#include "timers.h"
#include "irq.h"
#include "em_core.h"
#include "i2c.h"
#include "em_common.h"
#include "app_assert.h"
#include "app.h"
#include "ble.h"

/**************************************************************************//**
 * Global Variable
 *****************************************************************************/
// Load power management events
uint32_t events =0;


/**************************************************************************//**
 * schedulerSetEventUF function
 *****************************************************************************/
void schedulerSetEventUF(void)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();            // enter critical, turn off interrupts in NVIC

  sl_bt_external_signal(UFbitmask); // Set UF event

  CORE_EXIT_CRITICAL();             // exit critical, re-enable interrupts in NVIC
} // schedulerSetEventUF

/**************************************************************************//**
 * schedulerSetEventCOMP1 function
 *****************************************************************************/
void schedulerSetEventCOMP1(void)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();              // enter critical, turn off interrupts in NVIC

  sl_bt_external_signal(COMP1bitmask);// Set COMP1 event

  CORE_EXIT_CRITICAL();               // exit critical, re-enable interrupts in NVIC
}//schedulerSetEventCOMP1

/**************************************************************************//**
 * schedulerSetI2CEvent function
 *****************************************************************************/
void schedulerSetI2CEvent()
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();                // enter critical, turn off interrupts in NVIC

  sl_bt_external_signal(I2C_COMPLETED); // Set I2C_COMPLETE Event

  CORE_EXIT_CRITICAL();                 // exit critical, re-enable interrupts in NVIC
}//schedulerSetI2CEvent


/**************************************************************************//**
 * scheduler routine to return event to main()code and clear that event
 *****************************************************************************/
/*
uint32_t getNextEvent(void)
{

  uint32_t theEvent = 0;            // occurred events

  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();           // enter critical, turn off interrupts in NVIC

  if(events & UFbitmask)
  {
    theEvent = UFbitmask;          // pass the occurred UF event to main process
    events &= ~UFbitmask;          // clear the source of UF event
  }
  else if(events & COMP1bitmask)
  {
    theEvent = COMP1bitmask;       // pass the occurred COMP1 event to main process
    events &= ~COMP1bitmask;       // clear the source of COMP1 event
  }
  else if(events & I2C_COMPLETED)
  {
    theEvent = I2C_COMPLETED;      // pass the occurred I2C_COMPLETE event to main process
    events &= ~I2C_COMPLETED;      // clear the source of I2C_COMPLETE event
  }


  CORE_EXIT_CRITICAL();            // exit critical, re-enable interrupts in NVIC

  return theEvent;                 // return event to main process

} // getNextEvent()
*/


/**************************************************************************//**
 * temperature sensor finite state machine
 *****************************************************************************/
void temperature_state_machine(sl_bt_msg_t* event)
{
  if(SL_BT_MSG_ID(event->header) == sl_bt_evt_system_external_signal_id)
  {
      ble_data_struct_t* ble_event = get_ble_data();

      my_states curr_state;                                               // current state
      static my_states next_state = IDLE;                                 // next state

      curr_state = next_state;                                            // next event to current state

      switch (curr_state)
      {
        case IDLE:
          // runs FSM only if the BLE connection is open and indication is enable and stops taking measurement once BLE is disconnected
          // or HTM indication is disabled
          if((ble_event->connectionOpen) && (ble_event->conectionClose == false) && (ble_event->htm_indication_enable))
          {
              if(event->data.evt_system_external_signal.extsignals & UF_EVENT) // Under flow event occurred
              {
                  GPIO_PinOutSet(gpioPortD, I2C_ENABLE);                      // enable the i2c sensor
                  timerWaitUs_irq(_Poweruptime);                              // load timer COMP1 for power up time of 80ms
                  next_state = I2C_COMMAND;                                   // Jump to I2C_COMMAND state
              }
          }
          break;

         case I2C_COMMAND:
           if(event->data.evt_system_external_signal.extsignals & COMP1_EVENT) // COMP1 Occurred, elapsed power up time
           {
               sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1); // add em1 power requirement
               init_temp();                                               // initialize i2c
               start_temp_I2CWrite();                                     // i2c write command
               next_state = I2C_WAIT;                                     // jump to I2C_WAIT state
           }
           break;

        case I2C_WAIT:
          if(event->data.evt_system_external_signal.extsignals & I2C_COMPLETE) // I2C write command complete
          {
              NVIC_DisableIRQ(I2C0_IRQn);                                  // Disable the I2C0 interrupt
              sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);// remove em1 power requirement
              timerWaitUs_irq(_14bitCONVTIME);                             // load timer COMP1 for conversion time of 10.8ms
              next_state = I2C_READ;                                       // jump to I2C_READ state

          }
          break;

        case I2C_READ:
          if(event->data.evt_system_external_signal.extsignals & COMP1_EVENT) // COMP1 Occurred, elapsed conversion time
          {
             sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);    // add em1 power requirement
             Read_TemperatureSensor();                                     // Read the temperature sensor
             next_state = CONVERT_TEMP_TO_C;                               // Jump to CONVERT_TEMP_TO_C state
          }
          break;

        case CONVERT_TEMP_TO_C:
          if(event->data.evt_system_external_signal.extsignals & I2C_COMPLETE) // I2C read complete
          {
              NVIC_DisableIRQ(I2C0_IRQn);                                   // Disable the I2C0 interrupt
              sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1); // remove em1 power requirement
              Convert_TemperatureSensor();                                  // convert temperature to celsius
              GPIO_PinOutClear(gpioPortC, I2C_SCL);                         // disable the i2c clock
              GPIO_PinOutClear(gpioPortC, I2C_SDA);                         // disable the i2c data line
              GPIO_PinOutClear(gpioPortD, I2C_ENABLE);                      // disable the i2c
              next_state = IDLE;                                            // jump to IDLe state
          }
          break;

        default:
          // invalid case
          break;
      }
  }

}

