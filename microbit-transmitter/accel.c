#include <stdint.h>
#include "accel.h"
#include "twi.h"

#define ACCEL_ADDR			0x01D
#define ACCEL_DATA_REG		0x01
#define ACCEL_CTRL_REG_1	0x2A
#define ACCEL_200_HZ_ON		0x11

void accel_init(){
	uint8_t data = ACCEL_200_HZ_ON;
	twi_multi_write(ACCEL_ADDR, ACCEL_CTRL_REG_1, 1, &data);
}

void accel_read_x_y_z(int * data_buffer){
	uint8_t raw_data[6] = {0, 0, 0, 0, 0, 0};
	twi_multi_read(ACCEL_ADDR, ACCEL_DATA_REG, 6, raw_data);

	int16_t x_accel, y_accel, z_accel;

	// MSB and LSB are in 2s complement,
	// but LSB only contains two bits
	x_accel = (raw_data[0] << 8) | raw_data[1];
	x_accel = -(x_accel >> 6);
	y_accel = (raw_data[2] << 8) | raw_data[3];
	y_accel = -(y_accel >> 6);
	z_accel = (raw_data[4] << 8) | raw_data[5];
	z_accel = -(z_accel >> 6);

	data_buffer[0] = (int)x_accel;
	data_buffer[1] = (int)y_accel;
	data_buffer[2] = (int)z_accel;
}
