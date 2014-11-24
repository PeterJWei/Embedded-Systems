KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o

# All core kernel objects go here.  Add objects here if you need to.
SYSCALLS := syscall/C_swi_handler.o syscall/C_irq_handler.o syscall/read.o syscall/write.o syscall/time.o syscall/include.o
KOBJS := assert.o main.o math.o memcheck.o raise.o ctype.o hexdump.o device.o user_setup.o swi_handler.o irq_handler.o globals.o printvar.o ic_setup.o check_ic.o ack_intr.o disable_interrupts.o $(SYSCALLS)
KOBJS := $(KOBJS:%=$(KDIR)/%)
ALL_OBJS += $(KOBJS) $(KSTART)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk
-include $(KDIR)/syscall/kernel.mk
-include $(KDIR)/sched/kernel.mk
-include $(KDIR)/lock/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS)
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)

