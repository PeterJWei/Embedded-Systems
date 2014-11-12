@ irq_handler.S: IRQ Handler
@
    .extern irq_setup_stack_ptr
    .extern C_IRQ_Handler

    .file   "irq_handler.S"
    .text

    .global irq_handler
irq_handler:
    mov     sp, #0xa4000000
    stmfd   sp!, {r0-r12, lr}

    bl      ack_intr
    
    bl      C_IRQ_Handler

    ldmfd   sp!, {r0-r12, lr}
    movs    pc, lr
