@ enable_irq.S: helper function written in asm called from kernel
@
@ Hint:
@   CPSR:
@       N|Z|C|V| [27:9] |I|F|T|M[4:0]
@   I -> 1
@   F -> 1
@   T -> T
@   CPSR_SVC = 0x10011 -> CPSR_USER = 0x10000

    .file   "enable_irq.S"
    .text

    .global enable_irq
enable_irq:
    @ Save gp registers, lr, and cpsr so that we can return to kernel main later.
    stmfd   sp!, {r1-r12, lr}

    mrs     r2, cpsr
    bic     r2, r2, #0x080 @enable irqs
    msr     cpsr, r2

    ldmfd   sp!, {r1-r12, lr}
