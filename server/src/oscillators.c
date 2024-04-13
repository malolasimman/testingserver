/***************************************************************************//**
 *
 * @file oscillators.c
 * @brief This code involves initializing the clock for low energy timer0 for EFR32BG13
 * Created on: Jan 30, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 4
 *
 ******************************************************************************/


/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "oscillators.h"
#include "em_cmu.h"
#include "app.h"

/**************************************************************************//**
 * Clock management unit initialization function
 *****************************************************************************/
void cmu_init()
{
  // If the lowest energy mode is EM0, EM1, EM2 configure for LFXO
  if(LOWEST_ENERGY_MODE == EM0 || LOWEST_ENERGY_MODE == EM1 || LOWEST_ENERGY_MODE == EM2)
  {
      // Enable the Low Frequency Crystal Oscillator (LFXO)
      CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

      // Select LFXO as clock source for Low Frequency Clock A (LFA)
      CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);

      // Set clock divider for LETIMER0 clock source to divide by 4
      CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_4);

      // Enable clock for LETIMER0
      CMU_ClockEnable(cmuClock_LETIMER0,true);
  }

  // If the lowest energy mode is EM3, configure for ULFRCO
  if(LOWEST_ENERGY_MODE == EM3)
  {
      // Enable the Ultra Low Frequency RC Oscillator (ULFRCO)
      CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);

      // Select ULFRCO as clock source for Low Frequency Clock A (LFA)
      CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_ULFRCO);

      // Set clock divider for LETIMER0 clock source to divide by 1 (no division)
      CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_1);

      // Enable clock for LETIMER0
      CMU_ClockEnable(cmuClock_LETIMER0,true);

  }

}

