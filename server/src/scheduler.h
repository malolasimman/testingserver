/***************************************************************************//**
 *
 * @file scheduler.h
 * @brief This code involves scheduler declarations
 * Created on: Feb 15, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 6,8
 *
 ******************************************************************************/

#ifndef SRC_SCHEDULER_H_
#define SRC_SCHEDULER_H_

/**************************************************************************//**
 * Headers
 *****************************************************************************/

#include "em_core.h"
#include "app.h"
#include "sl_bt_api.h"
/**************************************************************************//**
 * Macros
 *****************************************************************************/
#define UFbitmask (1) // underflow bit mask
#define COMP1bitmask (2) // comp1 bit mask
#define I2C_COMPLETED (4) // I2C bit mask

/**************************************************************************//**
 * function declarations
 *****************************************************************************/
// scheduler function declarations
void schedulerSetEventUF(void);
void schedulerSetEventCOMP1(void);
uint32_t getNextEvent(void);
void schedulerSetI2CEvent();
void temperature_state_machine(sl_bt_msg_t* event);

#endif /* SRC_SCHEDULER_H_ */
