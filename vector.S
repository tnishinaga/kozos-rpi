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
    nop

Undefined_Addr:
Prefetch_Addr:
Abort_Addr:
    @ TODO: error handling
1:
    wfi @ goto sleep
    b 1b

Reset_Addr:
    b _start

SVC_Addr:
    @ enter SVC mode
    b SVC_Handler_asm @ not return
IRQ_Addr:
    @ enter IRQ mode
    b IRQ_Handler_asm @ not return