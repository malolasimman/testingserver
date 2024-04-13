/***************************************************************************//**
 *
 * @file i2c.h
 * @brief This code involves i2c function declarations
 * Created on: Feb 14, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 6
 *
 ******************************************************************************/

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

/**************************************************************************//**
 * Headers
 *****************************************************************************/

#include "em_device.h"
#include "em_i2c.h"
#include "sl_i2cspm.h"

/**************************************************************************//**
 * Macros
 *****************************************************************************/
#define I2C_SCL    (10)       // i2c0 temp sensor SCL
#define I2C_SDA    (11)       // i2c0 temp sensor SDA
#define I2C_ENABLE (15)       // i2c0 temp sensor ENABLE
#define SI7021_DEVICE_ADDR (0x40) // 7 bit slave address


/**************************************************************************//**
 * function declarations
 *****************************************************************************/
void init_temp(void);
void start_temp_I2CWrite(void);
void read_temp_from_si7021(void);
void Read_TemperatureSensor(void);
void Convert_TemperatureSensor(void);

#endif /* SRC_I2C_H_ */
