PROGS_ROT_OBJS := rot13.o
PROGS_ROT_OBJS := $(PROGS_ROT_OBJS:%=$(TDIR)/rot13/%)
ALL_OBJS += $(PROGS_ROT_OBJS)

$(TDIR)/bin/rot13 : $(TSTART) $(PROGS_ROT_OBJS) $(TLIBC)
