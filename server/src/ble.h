/***************************************************************************//**
 *
 * @file ble.h
 * @brief This code involves ble function declarations
 * Created on: Feb 20, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 10
 *            https://github.com/SiliconLabs/bluetooth_applications/blob/master/bluetooth_thermometer_with_efr32_internal_temperature_sensor/src/app.c
 *
 ******************************************************************************/
#ifndef SRC_BLE_H_
#define SRC_BLE_H_

#include "sl_bt_api.h"
#include "app.h"
#include "sl_bluetooth.h"
#include "sl_status.h"             // for sl_status_print()
#include "gatt_db.h"
#include "stdbool.h"

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#define MIN_ADV (250 * 1.6)
#define MAX_ADV (250 * 1.6)
#define MIN_INTERVAL (75 / 1.25)
#define MAX_INTERVAL (75 / 1.25)
#define SLAVE_LATENCY (4)
#define TIMEOUT (760)

#define UINT8_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); }
#define UINT32_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                    *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24); }
#define UINT32_TO_FLOAT(m, e) (((uint32_t)(m) & 0x00FFFFFFU) | (uint32_t)((int32_t)(e) << 24))


// BLE Data Structure, save all of our private BT data in here.
// Modern C (circa 2021 does it this way)
// typedef ble_data_struct_t is referred to as an anonymous struct definition
typedef struct {

  // values that are common to servers and clients
  bd_addr myAddress;
  uint8_t myAddressType;
  bool htm_indication_enable;
  bool conectionClose;
  bool connectionOpen;

  // values unique for server
  // The advertising set handle allocated from Bluetooth stack.
  uint8_t advertisingSetHandle;
  uint8_t connectionHandle;
  bool in_flight;
  bool ok_to_send_htm_indications; // true when client enabled indications

  // values unique for client


} ble_data_struct_t;

/**************************************************************************//**
 * function declarations
 *****************************************************************************/
void handle_ble_event(sl_bt_msg_t* evt);

ble_data_struct_t* get_ble_data();

void inidcate_temp(uint32_t temperature);

#endif /* SRC_BLE_H_ */
