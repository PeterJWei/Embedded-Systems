@ irq_handler.S: IRQ Handler
@
    .extern irq_setup_stack_ptr
    .extern C_IRQ_Handler

    .file   "irq_handler.S"
    .text

    .global irq_handler
irq_handler:
    ldr     sp, =0xa0800000
    stmfd   sp!, {r0-r12, lr}

    bl      C_IRQ_Handler
    bl      ack_intr

    ldmfd   sp!, {r0-r12, lr}
    movs    pc, lr
