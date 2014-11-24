SYSCALL_OBJS := io.o proc.o time.o read.o write.o C_irq_handler.o C_swi_handler.o include.o
SYSCALL_OBJS := $(SYSCALL_OBJS:%=$(KDIR)/syscall/%)

KOBJS += $(SYSCALL_OBJS)
