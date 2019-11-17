#include "stdint.h"
//#include "gpio.h"

void twi_init();
void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read, uint8_t* data_buffer);
void twi_multi_write(uint8_t slave_address, uint8_t start_register, int registers_to_write, uint8_t* data_buffer);

#define TWI0 ((NRF_TWI_REG *)0x40003000)


typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t RESERVED0[1];
    volatile uint32_t STARTTX;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t STOP;
    volatile uint32_t RESERVED2[1];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESUME;

    volatile uint32_t RESERVED3[56];
    volatile uint32_t STOPPED;
    volatile uint32_t RXDREADY;
    volatile uint32_t RESERVED4[4];
    volatile uint32_t TXDSENT;
    volatile uint32_t RESERVED5[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED6[4];
    volatile uint32_t BB;

    volatile uint32_t RESERVED7[49];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED8[63];
    volatile uint32_t INTEN;
    volatile uint32_t INTSET;
    volatile uint32_t INTCLR;
    volatile uint32_t RESERVED9[110];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED10[14];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED11[1];
    volatile uint32_t PSELSCL;
    volatile uint32_t PSELSDA;
    volatile uint32_t RESERVED13[2];
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED14[1];
    volatile uint32_t FREQUENCY;
    volatile uint32_t RESERVED15[24];
    volatile uint32_t ADDRESS;
} NRF_TWI_REG;