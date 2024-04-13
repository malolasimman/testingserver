/***************************************************************************//**
 *
 * @file i2c.c
 * @brief This code involves i2c function definitions
 * Created on: Feb 14, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 6, 8
 *
 ******************************************************************************/

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "i2c.h"
#include "scheduler.h"
#include "ble.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

/**************************************************************************//**
 * Global Variables
 *****************************************************************************/
I2C_TransferSeq_TypeDef transferSequence;           // make this global for IRQs in A4
uint8_t cmd_data = 0xF3;                            // make this global for IRQs in A4
uint16_t read_data;                                 // make this global for IRQs in A4


/**************************************************************************//**
 * I2C init function
 *****************************************************************************/
void init_temp(void)
{
  I2CSPM_Init_TypeDef I2C_Config =
  {
      .port = I2C0,
      .sclPort = gpioPortC,
      .sclPin = I2C_SCL,
      .sdaPort = gpioPortC,
      .sdaPin = I2C_SDA,
      .portLocationScl = 14,
      .portLocationSda = 16,
      .i2cRefFreq = 0,
      .i2cMaxFreq = I2C_FREQ_STANDARD_MAX,
      .i2cClhr = i2cClockHLRStandard
  };
  I2CSPM_Init(&I2C_Config);

//  uint32_t i2c_bus_frequency = I2C_BusFreqGet (I2C0);
//  LOG_INFO("i2c_bus_frequency = %lu Hz \r\n", i2c_bus_frequency);

}

/**************************************************************************//**
 * start_temp function is to send command to start measure the temperature
 *****************************************************************************/
void start_temp_I2CWrite(void){
  // Send Measure Temperature command
  I2C_TransferReturn_TypeDef transferStatus;
  transferSequence.addr = SI7021_DEVICE_ADDR << 1;    // shift device address left
  transferSequence.flags = I2C_FLAG_WRITE;
  transferSequence.buf[0].data = &cmd_data;           // pointer to data to measure temperature
  transferSequence.buf[0].len = sizeof(cmd_data);

  NVIC_EnableIRQ(I2C0_IRQn);
  transferStatus = I2C_TransferInit (I2C0, &transferSequence);

  if (transferStatus < 0)
  {
      LOG_ERROR("I2C_TransferInit() Write error = %d \r\n", transferStatus);
  }
}

/**************************************************************************//**
 * Read_TemperatureSensor function is to read the temperature measurement
 *****************************************************************************/
void Read_TemperatureSensor(void){

  // Send Measure Temperature command
  I2C_TransferReturn_TypeDef transferStatus;
  transferSequence.addr = SI7021_DEVICE_ADDR << 1;    // shift device address left
  transferSequence.flags = I2C_FLAG_READ;
  transferSequence.buf[0].data = (uint8_t *)&read_data; // pointer to data to write
  transferSequence.buf[0].len = sizeof(read_data);

  NVIC_EnableIRQ(I2C0_IRQn);
  transferStatus = I2C_TransferInit (I2C0, &transferSequence);

  if (transferStatus < 0)
  {
      LOG_ERROR("I2C_TransferInit() Read error = %d \r\n", transferStatus);
  }
}
/**************************************************************************//**
 * Convert_TemperatureSensor function converts temperature to degree celcius
 *****************************************************************************/
void Convert_TemperatureSensor(void){
  uint8_t msb = read_data >> 8;
  uint8_t lsb = read_data;
  float TempVal = msb | (lsb << 8);
  // Converting to degree
  TempVal = ((175.72*TempVal)/65536) - 46.85;
  inidcate_temp((uint32_t)TempVal);
//  LOG_INFO("temperature reading = %d C \r\n", (int)TempVal);

}

