@ swi_handler.S: SWI Handler
@
@ Author: Harry Q Bovik <hqbovik@andrew.cmu.edu>
@ and Group 17
@ Peter Wei (pwei) and Vruti Sivakumaran (vsivakum)
@ Date:   Tue, 23 Oct 2007 11:20:33 -0400
@
@ Hint: To change the SWI handler in class, we need to accommodate a return
@   value from the C_SWI_Handler.

    .extern C_SWI_Handler
    .extern global_data

    .file   "swi_handler.S"
    .text

    .global swi_handler
swi_handler:
    mrs     ip, spsr
    stmfd   sp, {ip, sp, lr}^
    add     sp, sp, #-12

    sub     sp, sp, #4
    stmfd   sp!, {r0-r12, lr}

    ldr     r8, =global_data @reload r8
    ldr     r8, [r8]

    mrs     r3, cpsr
    bic     r3, #0x80
    msr     cpsr, r3
    @ get spsr into general purpose (gp) registers
    mrs     r2, spsr

    @ store spsr above gp registers
    str     r2, [sp, #14*4]

    @ Set Param 1: extract SWI and get SWI no. by bit-masking
    ldr     r0, [lr, #-4]
    bic     r0, r0, #0xff000000

    @ Set Param 2: pointer to parameters on stack
    mov     r1, sp

    @ go to handler
    bl      C_SWI_Handler
    @ restore spsr
    ldr     r2, [sp, #14*4]
    msr     spsr, r2

@    mrs     r3, cpsr
@    orr     r3, #0x80
@    msr     cpsr, r3
    @ Discard the r0 on the stack (r0 has ret value).
    add     sp, sp, #4
    ldmfd   sp!, {r1-r12, lr}
    add     sp, sp, #4

    ldmfd   sp, {ip, sp, lr}^
    add     sp, sp, #12
    msr     spsr, ip

    @ remove space used to store spsr
    movs    pc, lr
