.global Vector_Table
.align 4
Vector_Table:
    ldr pc, Reset_Addr
    ldr pc, Undefined_Addr
    ldr pc, SVC_Addr
    ldr pc, Prefetch_Addr
    ldr pc, Abort_Addr
    nop
    ldr pc, IRQ_Addr
FIQ_Handler:
    @ 4KB max
1:
    wfi
    b 1b

Reset_Addr:
    .word _start
Undefined_Addr:
    .word undefined_fault
Prefetch_Addr:
    .word prefetch_fault
Abort_Addr:
    .word abort_fault
IRQ_Addr:
    .word IRQ_Handler_asm
SVC_Addr:
    .word SVC_Handler_asm
.global Vector_Table_end
Vector_Table_end:
    nop

undefined_fault:
    wfi
    b undefined_fault

prefetch_fault:
    subs pc, lr, #4
1:
    wfi
    b 1b

abort_fault:
    wfi
    b abort_fault