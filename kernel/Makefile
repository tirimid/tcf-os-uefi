COMMONDIR = ../common
LIBCDIR = ../libc

IMEDDIR = imed
SRCDIR = src
INCDIR = inc
BUILDDIR = build

CC = clang
CFLAGS = -std=c11 -pedantic -target x86_64-elf -I$(INCDIR) -ffreestanding \
	 -I$(COMMONDIR)/inc -I$(LIBCDIR)/inc

OBJS = $(IMEDDIR)/main.o $(IMEDDIR)/kernel.o $(IMEDDIR)/gfx.o \
       $(IMEDDIR)/string.o

LD = clang
LDS = linker.ld
LDFLAGS = -ffreestanding -nostdlib -T$(LDS) -Bsymbolic -static -e kernel_main

ELF = kernel.elf

all:
	make clean
	make build
	@ echo "target 'all' complete"

clean:
	rm $(IMEDDIR)/* $(BUILDDIR)/*
	@ echo "target 'clean' complete"

build: $(BUILDDIR)/$(ELF)
	@ echo "target 'build' complete"

$(BUILDDIR)/$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMEDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMEDDIR)/%.o: $(LIBCDIR)/src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
