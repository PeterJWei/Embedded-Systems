KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o

# All core kernel objects go here.  Add objects here if you need to.
SYSCALLS := syscalls/C_swi_handler.o syscalls/C_irq_handler.o syscalls/read.o syscalls/write.o syscalls/time.o syscalls/sleep.o syscalls/include.o syscalls/exit_handler.o
KOBJS := assert.o main.o raise.o user_setup.o swi_handler.o irq_handler.o globals.o printvar.o ic_setup.o check_ic.o ack_intr.o $(SYSCALLS)
KOBJS := $(KOBJS:%=$(KDIR)/%)
ALL_OBJS += $(KOBJS) $(KSTART)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS)
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)

