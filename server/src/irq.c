/***************************************************************************//**
 *
 * @file irq.c
 * @brief This code involves irq handler definitions
 * Created on: Feb 14, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 5
 *
 ******************************************************************************/

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "irq.h"
#include "em_letimer.h"
#include "gpio.h"
#include "em_core.h"
// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"
#include "i2c.h"
#include "timers.h"
#include "em_cmu.h"

/**************************************************************************//**
 * Global Variable
 *****************************************************************************/
//Timer ticks
uint32_t timeTicks =0;

/**************************************************************************//**
 * Low Energy Timer0 Interrupt handler
 *****************************************************************************/
 void LETIMER0_IRQHandler (void){

  // First: determine source of IRQ
  uint32_t flags = LETIMER_IntGetEnabled(LETIMER0);

  // Second: clear source of IRQ set in step 3
  LETIMER_IntClear(LETIMER0,flags);

  // Third: perform whatever processing is required
  if(flags & (LETIMER_IF_UF)){
      schedulerSetEventUF();
      timeTicks++;
  }

  if(flags & (LETIMER_IF_COMP1)){
      schedulerSetEventCOMP1();
  }

 }//LETIMER0_IRQHandler

 /**************************************************************************//**
  * letimerMilliseconds
  *****************************************************************************/
 uint32_t letimerMilliseconds(){

   uint32_t topValue = LETIMER_TopGet(LETIMER0); // Get topValue

   uint32_t Curr_count = LETIMER_CounterGet(LETIMER0);// Get current tick

   CORE_DECLARE_IRQ_STATE;

   CORE_ENTER_CRITICAL(); // enter critical, turn off interrupts in NVIC

   uint32_t time = timeTicks * LETIMER_PERIOD_MS; // calculate ticks

   CORE_EXIT_CRITICAL();  // exit critical, re-enable interrupts in NVIC

   topValue -= Curr_count;

   topValue = (topValue * SEC_US) / (CMU_ClockFreqGet(cmuClock_LETIMER0));

   time += topValue; // calculate current time
   return time;
 }//letimerMilliseconds

 /**************************************************************************//**
  * I2C Interrupt handler
  *****************************************************************************/
 void I2C0_IRQHandler(void)
 {
   I2C_TransferReturn_TypeDef transferStatus;

   transferStatus = I2C_Transfer(I2C0); // i2c transfer

   if (transferStatus == i2cTransferDone)
   {
       schedulerSetI2CEvent(); // set I2c complete event
   }
   if (transferStatus < 0)
   {
       LOG_ERROR("I2C Failed with the error %d \r\n", transferStatus);
   }
 } // I2C0_IRQHandler()

