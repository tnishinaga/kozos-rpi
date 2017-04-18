	.section .text
	.global	_start
#	.type	_start,@function
_start:
    @ jtag setup
	bl jtag_setup_asm
	@ set cpu mode
	@ TODO: write
	@ set svc stack pointer
	ldr sp, =_svcstack
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
    str r3, [r1, #4]!	@ [r0] = r3, r0++
    @ jump to clear_bss
    b clear_bss
clear_bss_done:
    @ goto main function
    bl main
1:
	wfi	@ sleep
	b	1b

	.global	dispatch
#	.type	dispatch,@function
dispatch:
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
