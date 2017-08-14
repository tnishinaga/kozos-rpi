#include "spi.h"

static inline int spi_init(int cs)
{
    // set gpio mode to spi
    // CE1: GPIO7:Alt0
    // CE0: GPIO8:Alt0
    // MISO: GPIO9:Alt0
    // MOSI: GPIO10:Alt0
    // SCLK: GPIO11:Alt0

    // set GPIO7 or 8 to Alt0
    uint32 mask = (uint32)0x07 << (3 * (8 - cs));
    uint32 sel = (uint32)0x04 << (3 * (8 - cs));
    // set GPIO9 to Alt0
    mask |= (uint32)(0x07 << (9 * 3)); 
    sel  |= (uint32)(0x04 << (9 * 3));
    *GPFSEL0 &= ~mask;
    *GPFSEL0 |= sel;

    // set GPIO10, 11 to Alt0
    *GPFSEL1 &= ~((uint32)((0x07 << 3 | 0x07)));
    *GPFSEL1 |= ((uint32)(0x04 << 3 | 0x04));

    return 0;
}

void spi_clock_div(uint16 clock_div)
{
    // set spi clock
    // SCLK = Core Clock / CDIV
    // SCLK = 250000000 / clock_div
    *SPI0_CLK = (uint16)clock_div;
}

int spi_start(int cs, int mode)
{
    if (bad_mode_range(mode)) {
        // bad mode number
        return -1;
    }
    if (bad_cs_range(cs)) {
        // bad cs number
        return -1;
    }

    // deactive spi transfer
    *SPI0_CS &= ~SPI0_CS_TA;

    // gpio setup
    spi_init(cs);

    // set spi mode
    // clear tx/rx fifo
    // select cs pin
    // spi transfer active
    *SPI0_CS = SPI0_CS_MODE(mode) 
            | SPI0_CS_CSPOL_HIGH
            | SPI0_CS_CLEAR_RX 
            | SPI0_CS_CLEAR_TX
            | cs
            | SPI0_CS_TA;
    return 0;
}

static inline uint8 spi_read(void)
{
    // wait until data received
    while(!(*SPI0_CS & SPI0_CS_RXD));
    // return read data
    return *SPI0_FIFO;
}

int spi_write(uint8 data)
{
    // wait until buffer can accept data
    while(!(*SPI0_CS & SPI0_CS_TXD));
    // write data
    *SPI0_FIFO = data;
    // wait until transfar done
    while(!(*SPI0_CS & SPI0_CS_DONE));
    
    // return recieved data
    return spi_read();
}


int spi_end(void)
{
    *SPI0_CS &= ~SPI0_CS_TA;
    return 0;
}