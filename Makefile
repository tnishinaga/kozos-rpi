PREFIX  = /usr/
ARCH    = arm-none-eabi
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

OBJS  = startup.o main.o interrupt.o vector.o interrupt_handler.o
OBJS += lib.o serial.o spi.o

# sources of kozos
OBJS += kozos.o syscall.o memory.o consdrv.o command.o

TARGET = kozos

CFLAGS = -Wall -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I.
CFLAGS += -g3
CFLAGS += -Os
CFLAGS += -march=armv6kz -mtune=arm1176jzf-s
CFLAGS += -DKOZOS

LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o
.SUFFIXES: .S .o
.SUFFIXES: .elf .bin

all : $(TARGET).bin

$(TARGET).elf :	$(OBJS)
		$(CC) $(OBJS) -o $@ $(CFLAGS) $(LFLAGS)

.elf.bin:
	$(OBJCOPY) -O binary $< $@

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

.s.o :		$<
		$(CC) -c $(CFLAGS) $<

.S.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf
