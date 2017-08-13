#ifndef RPILIB_PERIPHERALS_H
#define RPILIB_PERIPHERALS_H

#include "defines.h"

#define RPI_CORE_CLOCK  250000000 // 250MHz

#define PHY_PERI_ADDR(x) (0x20000000 + (x))

// GPIO Peripheral
#define GPIO_BASE	(0x00200000)
#define GPFSEL0		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x00))
#define GPFSEL1		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x04))
#define GPFSEL2		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x08))
#define GPFSEL3		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x0c))
#define GPFSEL4		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x10))
#define GPFSEL5		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x14))
#define GPSET0		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x1c))
#define GPSET1		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x20))
#define GPCLR0		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x28))
#define GPCLR1		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x2c))
#define GPLEV0		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x34))
#define GPLEV1		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x38))
// for GPFSEL mask
// use AND mask
#define GPFSEL_MASK_IN(n)	(~(volatile uint32)(0x07 << ((n % 10) * 3)))
// use OR mask
#define GPFSEL_MASK_OUT(n)	(0x01 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT0(n)	(0x04 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT1(n)	(0x05 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT2(n)	(0x06 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT3(n)	(0x07 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT4(n)	(0x03 << ((n % 10) * 3))
#define GPFSEL_MASK_ALT5(n)	(0x02 << ((n % 10) * 3))
// GPIO PULLUP/DOWN
#define GPPUD 		((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x94))
#define GPPUDCLK0	((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x98))
#define GPPUDCLK1	((volatile uint32 *)PHY_PERI_ADDR(GPIO_BASE + 0x9C))


// SystemTimer Peripheral
#define SYST_BASE	(0x00003000)
#define SYST_CS		((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x00))
#define SYST_CLO	((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x04))
#define SYST_CHI	((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x08))
#define SYST_C0		((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x0c))
#define SYST_C1		((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x10))
#define SYST_C2		((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x14))
#define SYST_C3		((volatile uint32 *)PHY_PERI_ADDR(SYST_BASE + 0x18))


// UART peripheral
#define UART0_BASE		0x00201000
#define UART0_DR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x00))
#define UART0_RSRECR	((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x04))
#define UART0_FR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x18))
// #define UART0_ILPR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x20)) // not use
#define UART0_IBRD		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x24))
#define UART0_FBRD		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x28))
#define UART0_LCRH		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x2c))
#define UART0_CR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x30))
#define UART0_IFLS		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x34))
#define UART0_IMSC		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x38))
#define UART0_RIS		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x3c))
#define UART0_MIS		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x40))
#define UART0_ICR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x44))
#define UART0_DMACR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x48))
#define UART0_ITCR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x80))
#define UART0_ITIP		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x84))
#define UART0_ITOP		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x88))
#define UART0_TDR		((volatile uint32 *)PHY_PERI_ADDR(UART0_BASE + 0x8c))


// SPI0 peripheral
#define SPI0_BASE		(0x00204000)
#define SPI0_CS			((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x00))
#define SPI0_FIFO		((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x04))
#define SPI0_CLK		((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x08))
#define SPI0_DLEN		((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x0C))
#define SPI0_LTOH		((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x10))
#define SPI0_DC			((volatile uint32 *)PHY_PERI_ADDR(SPI0_BASE + 0x14))

// I2C(BSC1) peripheral
#define BSC1_BASE	(0x00804000)
#define BSC1_C		((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x00))
#define BSC1_S		((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x04))
#define BSC1_DLEN	((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x08))
#define BSC1_A		((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x0C))
#define BSC1_FIFO	((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x10))
#define BSC1_DIV	((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x14))
#define BSC1_DEL	((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x18))
#define BSC1_CLKT	((volatile uint32 *)PHY_PERI_ADDR(BSC1_BASE + 0x1C))


// Timer(ARM side) peripheral
#define TIMER_BASE			(0x0000B000)
#define TIMER_LOAD			((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x400))
#define TIMER_VALUE			((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x404))
#define TIMER_CONTROL		((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x408))
#define TIMER_IRQ_CLR		((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x40C))
#define TIMER_RAWIRQ		((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x410))
#define TIMER_MASKEDIRQ		((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x414))
#define TIMER_RELOAD		((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x418))
#define TIMER_PREDIVIDER	((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x41C))
#define TIMER_FREECOUNTER	((volatile uint32 *)PHY_PERI_ADDR(TIMER_BASE + 0x420))


// Interrupt
#define INTERRUPT_BASE					(0x0000B000)
#define INTERRUPT_IRQ_BASIC_PENDING		((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x200))
#define INTERRUPT_IRQ_PENDING1			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x204))
#define INTERRUPT_IRQ_PENDING2			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x208))
#define INTERRUPT_FIQ_CTRL				((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x20C))
#define INTERRUPT_ENABLE_IRQS1			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x210))
#define INTERRUPT_ENABLE_IRQS2			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x214))
#define INTERRUPT_ENABLE_BASIC_IRQS		((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x218))
#define INTERRUPT_DISABLE_IRQS1			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x21C))
#define INTERRUPT_DISABLE_IRQS2			((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x220))
#define INTERRUPT_DISABLE_BASIC_IRQS	((volatile uint32 *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x224))


#endif
