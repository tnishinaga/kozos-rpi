#pragma once

#include "spi.h"
#include "defines.h"

int enc28j60_init(void);
int enc28j60_send_packet(uint8 *data, uint32 len);
int enc28j60_spi_setup(uint8 cs, uint8 mode, uint16 clock_div);
int enc28j60_software_reset(void);