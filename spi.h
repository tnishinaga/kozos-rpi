#pragma once

#include "defines.h"
#include "rpi_peripherals.h"


#define SPI0_CS_LEN_LONG   (1 << 25)
#define SPI0_CS_DMA_LEN    (1 << 24)
#define SPI0_CS_CSPOL2     (1 << 23)
#define SPI0_CS_CSPOL1     (1 << 22)
#define SPI0_CS_CSPOL0     (1 << 21)
#define SPI0_CS_RXF        (1 << 20)
#define SPI0_CS_RXR        (1 << 19)
#define SPI0_CS_TXD        (1 << 18)
#define SPI0_CS_RXD        (1 << 17)
#define SPI0_CS_DONE       (1 << 16)
// #define SPI0_CS_TE_EN      (1 << 15)
// #define SPI0_CS_LMONO      (1 << 14)
#define SPI0_CS_LEN        (1 << 13)
#define SPI0_CS_REN        (1 << 12)
#define SPI0_CS_ADCS       (1 << 11)
#define SPI0_CS_INTR       (1 << 10)
#define SPI0_CS_INTD       (1 <<  9)
#define SPI0_CS_DMAEN      (1 <<  8)
#define SPI0_CS_TA         (1 <<  7)
#define SPI0_CS_CSPOL_HIGH (1 <<  6)
#define SPI0_CS_CLEAR_RX   (1 <<  5)
#define SPI0_CS_CLEAR_TX   (1 <<  4)
#define SPI0_CS_CPOL       (1 <<  3)
#define SPI0_CS_CPHA       (1 <<  2)
#define SPI0_CS_MODE(x)    (x <<  2)
#define SPI0_CS_CS(x)      (x)


void spi_clock_div(uint16 clock_div);
int spi_start(int cs, int mode);
int spi_write(uint8 data);
uint8 spi_read(void);
int spi_end(void);
