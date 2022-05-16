COMMONDIR = ../common
LIBCDIR = ../libc

IMEDDIR = imed
SRCDIR = src
INCDIR = inc
BUILDDIR = build

CC = clang
CFLAGS = -target x86_64-elf -std=c11 -pedantic -I$(INCDIR) -ffreestanding -I$(COMMONDIR)/inc \
	 -I$(LIBCDIR)/inc -mno-red-zone

AS = x86_64-elf-as
ASFLAGS =

LIBCOBJS = $(IMEDDIR)/lcstring.o $(IMEDDIR)/lcmath.o
OBJS = $(IMEDDIR)/main.o $(IMEDDIR)/ds.o $(IMEDDIR)/ctl.o $(IMEDDIR)/gfx.o $(IMEDDIR)/cpu.o \
       $(IMEDDIR)/pgalloc.o $(IMEDDIR)/page.o $(IMEDDIR)/heap.o $(IMEDDIR)/isr.o $(IMEDDIR)/idt.o \
       $(IMEDDIR)/state.o $(IMEDDIR)/gdt_0.o $(IMEDDIR)/pic.o $(IMEDDIR)/pit.o $(IMEDDIR)/error.o \
       $(IMEDDIR)/gdt_1.o

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

$(IMEDDIR)/%.o: $(SRCDIR)/*/%.s
	$(AS) $(ASFLAGS) -o $@ $^

$(IMEDDIR)/%.o: $(SRCDIR)/int/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -mgeneral-regs-only

$(IMEDDIR)/%.o: $(LIBCDIR)/src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
