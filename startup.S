#define CPSR_MODE_USER      0x10
#define CPSR_MODE_FIQ       0x11
#define CPSR_MODE_IRQ       0x12
#define CPSR_MODE_SVC       0x13
#define CPSR_MODE_MONITOR   0x16
#define CPSR_MODE_ABORT     0x17
#define CPSR_MODE_UNDEFINED 0x1b
#define CPSR_MODE_SYSTEM    0x1f
#define CPSR_THUMB          1 << 5
#define CPSR_FIQ_DIS        1 << 6
#define CPSR_IRQ_DIS        1 << 7
#define CPSR_ASYNC_ABORT    1 << 8
#define CPSR_ENDIAN_BE      1 << 9


    .section .text
	.global	_start
#	.type	_start,@function
_start:
    @ jtag setup
	bl jtag_setup_asm
	@ disable interrupt and enter system mode
    @ ldr r0, =(CPSR_ASYNC_ABORT | CPSR_IRQ_DIS | CPSR_FIQ_DIS | CPSR_MODE_SYSTEM)
    @ msr cpsr, r0
    cpsid aif, #0x1f
	@ set system stack pointer
	ldr sp, =_bootstack
	@ clear BSS
    @ r1: BSS start address
    @ r2: BSS end address
    @ r3: 0
    ldr r1, =_bss_start
    ldr r2, =_ebss
    movs r3, #0
clear_bss:
    @ if r1 == r2 then goto clear_bss_done
    cmp r1, r2
    beq clear_bss_done
    @ write 0 to memory
    str r3, [r1], #4	@ [r0] = r3, r0++
    @ jump to clear_bss
    b clear_bss
clear_bss_done:
    @ set vector table
    bl set_vector_table
    @ goto main function
    bl main
1:
	wfi	@ sleep
	b	1b

.global get_cpsr
get_cpsr:
    mrs r0, cpsr
    bx lr

.global set_vector_table
set_vector_table:
    ldr r0, =Vector_Table
    ldr r1, =Vector_Table_end
    mov r2, #0  @ vector table start address
1:
    @ if r0 == r1 then goto 1
    cmp r0, r1
    beq 2f
    ldr r3, [r0], #4
    str r3, [r2], #4
    @ jump to clear_bss
    b 1b
2:
    bx lr

@@@ JTAG setup @@@
@ 3.3V			: ARM_VREF
@ GPIO22 (ALT4): ARM_TRST
@ GPIO4  (ALT5): ARM_TDI
@ GPIO27 (ALT4): ARM_TMS
@ GPIO25 (ALT4): ARM_TCK
@ GPIO24 (ALT4): ARM_TDO
@ GND			: ARM_GND
jtag_setup_asm:
    ldr r1, =0x20200000 @ load GPFSEL address
    ldr r2, =0xffff8fff @ load GPIO4 mask
    ldr r3, =0xff1c0e3f @ load GPIO22,24,25,27 mask
    ldr r4, [r1, #0]    @ load GPFSEL0 value
    ldr r5, [r1, #8]    @ load GPFSEL2 value
    and r4, r4, r2      @ clear GPIO4 mode
    and r5, r5, r3      @ clear GPIO22,24,25,27 mode
    ldr r2, =0x00002000 @ load GPIO4 ALT4
    ldr r3, =0x0061b0c0 @ load GPIO22,24,25,27 ALT5
    orr r4, r4, r2      @ set GPIO4 mode to ALT4
    orr r5, r5, r3      @ set GPIO22,24,25,27 mode to ALT5
    str r4, [r1, #0]    @ save GPFSEL0 value
    str r5, [r1, #8]    @ save GPFSEL2 value
    bx lr
