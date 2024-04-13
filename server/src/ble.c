/***************************************************************************//**
 *
 * @file ble.c
 * @brief This code involves ble function definitions
 * Created on: Feb 20, 2024
 * Author: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * @student: Malola Simman Srinivasan Kannan, Malola.Srinivasankannan@Colorado.edu
 * Reference: Class lecture note 10
 *            https://github.com/SiliconLabs/bluetooth_applications/blob/master/bluetooth_thermometer_with_efr32_internal_temperature_sensor/src/app.c
 *
 ******************************************************************************/

/**************************************************************************//**
 * Headers
 *****************************************************************************/
#include "ble.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

/**************************************************************************//**
 * Global Variable
 *****************************************************************************/
// BLE private data
ble_data_struct_t ble_data;

/**************************************************************************//**
 * get_ble_data function
 *****************************************************************************/
ble_data_struct_t* get_ble_data ()
{
  return &ble_data;
}

/**************************************************************************//**
 * handle_ble_event function
 *****************************************************************************/
void handle_ble_event (sl_bt_msg_t *evt)
{

  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header))
    {

    // ******************************************************
    // Events common to both Servers and Clients
    // ******************************************************

    // --------------------------------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack API commands before receiving this boot event!
    // Including starting BT stack soft timers!
    // --------------------------------------------------------

    case sl_bt_evt_system_boot_id:
      {
        // handle boot event
        ble_data.conectionClose = false;
        ble_data.connectionOpen = false;
        ble_data.in_flight = false;
        ble_data.htm_indication_enable = false;

        // Extract unique ID from BT Address.
        sc = sl_bt_system_get_identity_address (&ble_data.myAddress,
                                                &ble_data.myAddressType);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_system_get_identity_address() returned != 0 status=0x%04x",
              (unsigned int) sc);
        }

        // Create an advertising set.
        sc = sl_bt_advertiser_create_set (&ble_data.advertisingSetHandle);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_advertiser_create_set() returned != 0 status=0x%04x",
              (unsigned int) sc);
        }

        // Set advertising interval to 250ms.
        sc = sl_bt_advertiser_set_timing (ble_data.advertisingSetHandle, // advertising set handle
            MIN_ADV, // min. adv. interval (250 milliseconds * 1.6)
            MAX_ADV, // max. adv. interval (250 milliseconds * 1.6)
            0, // adv. duration
            0); // max. num. adv. events

        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_advertiser_set_timing() returned != 0 status=0x%04x",
              (unsigned int) sc);
        }

        // Start advertising and enable connections.
        sc = sl_bt_advertiser_start (ble_data.advertisingSetHandle,
                                     sl_bt_advertiser_general_discoverable,
                                     sl_bt_advertiser_connectable_scannable);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR("sl_bt_advertiser_start() returned != 0 status=0x%04x",
                    (unsigned int) sc);
        }
      }
      break;

      // --------------------------------------------------------------
      // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      {

        // handle open event
        ble_data.connectionOpen = true;
        ble_data.conectionClose = false;

        ble_data.connectionHandle = evt->data.evt_connection_opened.connection;

        // After connections is opened stops advertising
        sc = sl_bt_advertiser_stop (ble_data.advertisingSetHandle);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_advertiser_stop() returned != 0 status=0x%04x \r\n",
              (unsigned int) sc);
        }

        sc = sl_bt_connection_set_parameters (ble_data.connectionHandle,
        MIN_INTERVAL,
                                              MAX_INTERVAL,
                                              SLAVE_LATENCY,
                                              TIMEOUT, 0, 0xffff);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_connection_set_parameters() returned != 0 status=0x%04x \r\n",
              (unsigned int) sc);
        }
      }
      break;

      // --------------------------------------------------------------
      // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      {
        // handle close event
        ble_data.conectionClose = true;
        ble_data.connectionOpen = false;
        ble_data.htm_indication_enable = false;

        // Restart advertising after client has disconnected.
        sc = sl_bt_advertiser_start (ble_data.advertisingSetHandle,
                                     sl_bt_advertiser_general_discoverable,
                                     sl_bt_advertiser_connectable_scannable);
        if (sc != SL_STATUS_OK)
        {
          LOG_ERROR(
              "sl_bt_advertiser_start() returned != 0 status=0x%04x \r\n",
              (unsigned int) sc);
        }
      }
      break;

      // --------------------------------------------------------------
      // Informational. Triggered whenever the connection parameters are changed and at any time a connection is established
    case sl_bt_evt_connection_parameters_id:
      {
        LOG_INFO("BLE Connection params \r\n");
        LOG_INFO("handle = %d \r\n",
                 (int) evt->data.evt_connection_parameters.connection);
        LOG_INFO("interval = %d \r\n",
                 (int) (evt->data.evt_connection_parameters.interval*1.25));
        LOG_INFO("latency = %d \r\n",
                 (int) evt->data.evt_connection_parameters.latency);
        LOG_INFO("timeout = %d \r\n",
                 (int) evt->data.evt_connection_parameters.timeout*10);
      }
      break;

      // --------------------------------------------------------------
      // This event indicates that sl_bt_external_signal(myEvent) was called
      // and returns the myEvent value in the event data structure: evt->data.evt_system_external_signal.extsignals
    case sl_bt_evt_system_external_signal_id:

      break;

      // ******************************************************
      // Events for Servers
      // ******************************************************

      // Indicates either:A local Client Characteristic Configuration descriptor (CCCD) was changed by the remote GATT client, or
      // That a confirmation from the remote GATT Client was received upon a successful reception of the indication
      // I.e. we sent an indication from our server to the client with sl_bt_gatt_server_send_indication()
    case sl_bt_evt_gatt_server_characteristic_status_id:
      {
        if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temperature_measurement)
        {
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_indication)
                  ble_data.htm_indication_enable = true;

                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_disable)
                  ble_data.htm_indication_enable = false;
            }
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
              ble_data.in_flight = false;
          }
      }
      break;

      // Possible event from calling sl_bt_gatt_server_send_indication() -
      // i.e. we never received a confirmation for a previously transmitted indication.
    case sl_bt_evt_gatt_server_indication_timeout_id:
      {
        ble_data.in_flight = true;
        LOG_ERROR("Recieved indication timeout from client \r\n");
      }
      break;

    } // end - switch

} // handle_ble_event()


/**************************************************************************//**
 * inidcate_temp function
 *****************************************************************************/
void inidcate_temp(uint32_t temperature){
    uint8_t temp[5];
    uint8_t flag = 0;
    uint8_t *ptr = temp;

    UINT8_TO_BITSTREAM(ptr, flag);
    uint32_t uint32_to_float_temp = temperature*1000;
    uint32_t htm_Temp = UINT32_TO_FLOAT(uint32_to_float_temp, -3);
    UINT32_TO_BITSTREAM(ptr, htm_Temp);

    // write to GATT server write attribute
    sl_status_t sc = sl_bt_gatt_server_write_attribute_value(gattdb_temperature_measurement, 0, 5, &temp[0]);
    if (sc != SL_STATUS_OK)
    {
      LOG_ERROR(
          "sl_bt_gatt_server_write_attribute_value() returned != 0 status=0x%04x \r\n",
          (unsigned int) sc);
    }

    // check bus validity
    if(ble_data.htm_indication_enable && !(ble_data.conectionClose) && (ble_data.connectionOpen) && !(ble_data.in_flight))
    {
        // send the data in BLE
        sc = sl_bt_gatt_server_send_indication(ble_data.connectionHandle, gattdb_temperature_measurement, 5 ,&temp[0]);
    }
    if (sc != SL_STATUS_OK)
    {
      LOG_ERROR(
          "sl_bt_gatt_server_send_indication() returned != 0 status=0x%04x \r\n",
          (unsigned int) sc);
    }
    else{
        // make in_flight on when sending data
        ble_data.in_flight = true;
    }
}
