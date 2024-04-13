/***************************************************************************//**
 *
 * @file timers.h
 * @brief This code involves i2c function declarations
 * Created on: Jan 30, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 6
 *
 ******************************************************************************/

#ifndef SRC_TIMERS_H_
#define SRC_TIMERS_H_

#include "em_letimer.h"

#define LETIMER_PERIOD_MS  (3000)
#define LETIMER_ON_TIME_MS (10)
#define SEC_US (1000000)
#define SEC_MS (1000)

void timerWaitUs(uint32_t us_wait);
void timerWaitUs_irq(uint32_t us_wait);

void initLETIMER0();

#endif /* SRC_TIMERS_H_ */
