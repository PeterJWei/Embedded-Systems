@ Group 17
@ Peter Wei (pwei) and Vruti Sivakumaran (vsivakum)
@ irq_handler.S: IRQ Handler
@
    .extern irq_setup_stack_ptr
    .extern C_IRQ_Handler
    .extern global_data

    .file   "irq_handler.S"
    .text

    .global irq_handler
irq_handler:
    ldr     sp, =0xa0800000
    stmfd   sp!, {r0-r12, lr}

    ldr     r8, =global_data @reload r8
    ldr     r8, [r8]
    bl      C_IRQ_Handler @increment the global timer
    bl      ack_intr @acknowledge interrupt

    ldmfd   sp!, {r0-r12, lr}
    movs    pc, lr
