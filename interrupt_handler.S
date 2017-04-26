#include "intr.h"

.global SVC_Handler_asm
SVC_Handler_asm:
    @ r13-r14(sp,lr): banked
    @ goto system mode
    ldr sp, =_intrstack
    @ push r0-r3 to intrstack
    push {r0-r3}
    mov r0, sp
    mrs r1, spsr
    mov r3, lr
    @ enter system mode
    cps #0x1f
    @ backup
    mov r2, sp
    @ push return address to stack
    push {r3}
    @ push r4-r12 to system stack
    push {r4-r12}
    @ restore original r0-r3 to r4-r7
    ldmia r0, {r4-r7}
    @ push r0-r3 to system stack
    push {r4-r7}
    @ push spsr to stack
    push {r1}
    @ push system mode sp and lr
    push {r2, lr}
    @ set interrupt type to r0
    mov r0, #SOFTVEC_TYPE_SYSCALL
    @ set stack pointer to r1
    mov r1, sp
    @ interrupt(softvec_type_t type, unsigned long sp)
    b interrupt
    @ not return

.global IRQ_Handler_asm
IRQ_Handler_asm:
    @ r0-r12: not banked
    @ r13-r14(sp,lr): banked
    @ goto system mode
    ldr sp, =_intrstack
    @ push r0-r3 to intrstack
    push {r0-r3}
    mov r0, sp
    mrs r1, spsr
    sub r3, lr, #4
    @ enter system mode
    cps #0x1f
    @ backup
    mov r2, sp
    @ push return address to stack
    push {r3}
    @ push r4-r12 to system stack
    push {r4-r12}
    @ restore original r0-r3 to r4-r7
    ldmia r0, {r4-r7}
    @ push r0-r3 to system stack
    push {r4-r7}
    @ push spsr to stack
    push {r1}
    @ push system mode sp and lr
    push {r2, lr}
    @ set interrupt type to r0
    mov r0, #SOFTVEC_TYPE_SERINTR
    @ set stack pointer to r1
    mov r1, sp
    @ interrupt(softvec_type_t type, unsigned long sp)
    b interrupt
    @ not return


@ void dispatch(kz_context *context);
@ typedef struct _kz_context {
@   uint32 sp; /* スタック・ポインタ */
@ } kz_context;
.global	dispatch
dispatch:
    ldr r0, [r0]
    @ set system mode sp and lr
    ldmia r0!, {sp, lr}
    @ enter svc mode
    cps #0x13
    @ set user sp to svc sp
    mov sp, r0
    @ restore spsr
    pop {r0}
    msr spsr_cxsf, r0
    @ pop r0-r12 and restore CPSR and return
    pop {r0-r3}
    pop {r4-r12}
    ldmfd sp!, {pc}^
