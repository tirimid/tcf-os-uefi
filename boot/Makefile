# the only change that should exist in gnu-efi is the change in data.c where
# some data structure members were set to NULL
GNUEFIDIR = ../gnu-efi
COMMONDIR = ../common
LIBCDIR = ../libc

IMEDDIR = imed
SRCDIR = src
INCDIR = inc
BUILDDIR = build

CC = clang
CFLAGS = -target x86_64-unknown-windows -ffreestanding -fshort-wchar \
	 -mno-red-zone -I$(GNUEFIDIR)/inc -I$(GNUEFIDIR)/inc/x86_64 \
	 -I$(GNUEFIDIR)/inc/protocol -I$(INCDIR) -std=c11 -pedantic \
	 -I$(COMMONDIR)/inc -I$(LIBCDIR)/inc

OBJS = $(IMEDDIR)/main.o $(IMEDDIR)/boot.o $(IMEDDIR)/io.o $(IMEDDIR)/mem.o \
       $(IMEDDIR)/gfx.o $(IMEDDIR)/string.o

LD = clang
LDFLAGS = -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main \
	  -Wl,-subsystem:efi_application -fuse-ld=lld-link

all:
	make clean
	make build
	@ echo "target 'all' complete"

clean:
	rm $(IMEDDIR)/* $(BUILDDIR)/*
	@ echo "target 'clean' complete"

build: $(BUILDDIR)/BOOTX64.EFI
	@ echo "target 'build' complete"

$(BUILDDIR)/BOOTX64.EFI: $(OBJS) $(IMEDDIR)/gnu-efi-data.o
	$(LD) $(LDFLAGS) -o $@ $^

$(IMEDDIR)/gnu-efi-data.o: $(GNUEFIDIR)/lib/data.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMEDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMEDDIR)/%.o: $(LIBCDIR)/src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
