.global SVC_Handler_asm
SVC_Handler_asm:
    @ r0-r12: not banked
    @ r13-r14(sp,lr): banked
    bl SVC_Handler
    bx lr

.global IRQ_Handler_asm
IRQ_Handler_asm:
    @ r0-r12: not banked
    @ r13-r14(sp,lr): banked
    bl IRQ_Handler
    bx lr