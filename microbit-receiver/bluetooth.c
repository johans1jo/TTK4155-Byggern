#include "bluetooth.h"
#include <string.h>

#include "nrf_sdm.h"
#include "ble.h"
#include "ble_gap.h"

extern uint8_t __data_start__;

uint32_t bluetooth_init(){
	uint32_t err_code = 0;

	err_code = sd_softdevice_enable(NULL, NULL);
	if(err_code){
		return err_code;
	}

	static ble_enable_params_t ble_enable_params;
	memset(&ble_enable_params, 0, sizeof(ble_enable_params));
	uint32_t app_ram_base = (uint32_t)&__data_start__;

	ble_enable_params.gap_enable_params.periph_conn_count = 1;
	ble_enable_params.common_enable_params.vs_uuid_count = 1;

	err_code = sd_ble_enable(&ble_enable_params, &app_ram_base);
	return err_code;
}

uint32_t bluetooth_gap_advertise_start(){
	uint32_t err_code = 0;

	static uint8_t adv_data[] = {
		15, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,
		'u', 'l', 'v', 'e', 'n', ' ', 'u', 't', ' ', 'a', 'v', ' ', 'E', 'U'
	};
	uint8_t adv_data_length = 16;

	sd_ble_gap_adv_data_set(adv_data, adv_data_length, NULL, 0);

	// Add more stuff
	ble_gap_adv_params_t adv_params;
	memset(&adv_params, 0, sizeof(adv_params));
	adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
	adv_params.interval = 0X085B;
	sd_ble_gap_adv_start(&adv_params);

	// Remove these lines when doing the GAP exercise
	//(void)adv_data;
	//(void)adv_data_length;

	return err_code;
}

uint32_t bluetooth_gatts_start(){
	uint32_t err_code = 0;

	return err_code;
}

void bluetooth_serve_forever(){
	// Comment all this in when doing GATT serving

	/*
	uint8_t ble_event_buffer[100] = {0};
	uint16_t ble_event_buffer_size = 100;

	while(1){
		if(m_matrix_attr_value != 0){
			// Matrix on
		}
		else{
			// Matrix off
		}

		while(
			sd_ble_evt_get(
				ble_event_buffer,
				&ble_event_buffer_size
			) != NRF_ERROR_NOT_FOUND
			){

			ble_evt_t * p_ble_event = (ble_evt_t *)ble_event_buffer;
			uint16_t event_id = p_ble_event->header.evt_id;

			switch(event_id){
				case BLE_GAP_EVT_CONNECTED:
					m_service_ubit.conn_handle =
						p_ble_event->evt.gap_evt.conn_handle;

					sd_ble_gatts_sys_attr_set(
						m_service_ubit.conn_handle,
						0,
						0,
						0
					);
					break;

				case BLE_GAP_EVT_DISCONNECTED:
					m_service_ubit.conn_handle =
						BLE_CONN_HANDLE_INVALID;

					bluetooth_gap_advertise_start();
					break;

				default:
					break;
			}

			ble_event_buffer_size = 100;
		}
		ble_event_buffer_size = 100;


	}
	*/
}
