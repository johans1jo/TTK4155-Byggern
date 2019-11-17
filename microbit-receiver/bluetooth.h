#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <stdint.h>

uint32_t bluetooth_init();

uint32_t bluetooth_gap_advertise_start();

uint32_t bluetooth_gatts_start();

void bluetooth_serve_forever();

#endif
