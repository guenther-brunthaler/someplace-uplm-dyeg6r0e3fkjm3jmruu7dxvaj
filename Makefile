TARGETS = uplm_s2ui
OTHERS = $(ENDIAN_27AQ18PTH4Y0M1ZZESYLKWJK5_GENERATED)

.PHONY: all clean

all: $(TARGETS)

include endian_27aq18pth4y0m1zzesylkwjk5.mk

clean:
	-rm $(TARGETS) $(OTHERS)

AUG_CFLAGS = $(CFLAGS) $(CPPFLAGS) -I .

uplm_s2ui_SOURCES = uplm_s2ui.c getopt_simplest.c getopt_simplest_perror.c
uplm_s2ui: $(uplm_s2ui_SOURCES) endian_27aq18pth4y0m1zzesylkwjk5.h
	$(CC) $(AUG_CFLAGS) $(LDFLAGS) -o $@ $(uplm_s2ui_SOURCES)
