/***************************************************************************//**
 * @file
 * @brief Application interface provided to main().
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * Editor: Feb 26, 2022, Dave Sluiter
 * Change: Added comment about use of .h files.
 *
 *
 *
 * Student edit: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student:    Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 *
 *
 ******************************************************************************/

// Students: Remember, a header file (a .h file) defines an interface
//           for functions defined within an implementation file (a .c file).
//           The .h file defines what a caller (a user) of a .c file requires.
//           At a minimum, the .h file should define the publicly callable
//           functions, i.e. define the function prototypes. #define and type
//           definitions can be added if the caller requires theses.

#ifndef APP_H
#define APP_H

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "em_core.h"

/**************************************************************************//**
 * Macros
 *****************************************************************************/
// Energy modes
#define EM0 (0)
#define EM1 (1)
#define EM2 (2)
#define EM3 (3)
#define LOWEST_ENERGY_MODE (EM2)  // current energy mode

#define _Poweruptime (80000)  // power up time in ms for i2c si7021
#define _14bitCONVTIME (10800)// 14 bit conversion time in ms for temperature sensor


/**************************************************************************//**
 * temperature sensor fsm states
 *****************************************************************************/
typedef enum fsm_states{
  IDLE,
  I2C_COMMAND,
  I2C_WAIT,
  I2C_READ,
  CONVERT_TEMP_TO_C
}my_states;

/**************************************************************************//**
 * temperature sensor fsm events
 *****************************************************************************/
typedef enum{
  UF_EVENT = 1,
  COMP1_EVENT = 2,
  I2C_COMPLETE = 4,
}events_t;

/**************************************************************************//**
 * function declarations.
 *****************************************************************************/
void app_init(void);
void app_process_action(void);

#endif // APP_H
