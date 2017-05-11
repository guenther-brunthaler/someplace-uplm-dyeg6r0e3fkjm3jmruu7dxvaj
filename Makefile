TARGETS = uplm_s2ui
OTHERS = $(ENDIAN_27AQ18PTH4Y0M1ZZESYLKWJK5_GENERATED)

.PHONY: all clean

all: $(TARGETS)

# Override this from command line for out-of-source builds.
srcdir = .

include $(srcdir)/endian_27aq18pth4y0m1zzesylkwjk5.mk

clean:
	-rm $(TARGETS) $(OTHERS)

AUG_CPPFLAGS = $(CPPFLAGS) -I $(srcdir) -I .
AUG_CFLAGS = $(AUG_CPPFLAGS) $(CFLAGS)

uplm_s2ui_SOURCES = \
	$(srcdir)/uplm_s2ui.c \
	$(srcdir)/getopt_simplest.c $(srcdir)/getopt_simplest_perror.c

uplm_s2ui: $(uplm_s2ui_SOURCES) endian_27aq18pth4y0m1zzesylkwjk5.h
	$(CC) $(AUG_CFLAGS) $(LDFLAGS) -o $@ $(uplm_s2ui_SOURCES)
