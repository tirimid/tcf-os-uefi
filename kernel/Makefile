COMMONDIR = ../common
LIBCDIR = ../libc

IMEDDIR = imed
SRCDIR = src
INCDIR = inc
BUILDDIR = build

CC = clang
CFLAGS = -std=c11 -pedantic -target x86_64-elf -I$(INCDIR) -ffreestanding -I$(COMMONDIR)/inc \
	 -I$(LIBCDIR)/inc

LIBCOBJS = $(IMEDDIR)/lcstring.o $(IMEDDIR)/lcmath.o
OBJS = $(IMEDDIR)/main.o $(IMEDDIR)/ds.o $(IMEDDIR)/ctl.o $(IMEDDIR)/gfx.o $(IMEDDIR)/cpu.o \
       $(IMEDDIR)/pgalloc.o $(IMEDDIR)/page.o $(IMEDDIR)/heap.o $(IMEDDIR)/isr.o $(IMEDDIR)/idt.o \
       $(IMEDDIR)/state.o $(IMEDDIR)/gdt.o $(IMEDDIR)/pic.o

LD = clang
LDS = linker.ld
LDFLAGS = -ffreestanding -nostdlib -T$(LDS) -Bsymbolic -static

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

$(BUILDDIR)/$(ELF): $(OBJS) $(LIBCOBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMEDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMEDDIR)/%.o: $(SRCDIR)/*/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMEDDIR)/%.o: $(SRCDIR)/int/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -mno-red-zone -mgeneral-regs-only

$(IMEDDIR)/%.o: $(LIBCDIR)/src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
