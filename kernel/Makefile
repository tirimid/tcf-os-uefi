GNUEFIDIR = ../gnu-efi
IMEDDIR = imed
SRCDIR = src
BUILDDIR = build
LIBDIR = lib

CC = x86_64-elf-gcc
CFLAGS = -Iinc -I$(GNUEFIDIR)/inc -fpic -ffreestanding -fno-stack-protector \
	 -fno-stack-check -mno-red-zone -fshort-wchar \
	 -maccumulate-outgoing-args -I$(GNUEFIDIR)/inc/x86_64

OBJS = $(IMEDDIR)/main.o

LD = x86_64-elf-ld
LDFLAGS = -shared -Bsymbolic -L$(LIBDIR) \
	  -T$(GNUEFIDIR)/gnuefi/elf_x86_64_efi.lds \
	  $(LIBDIR)/crt0-efi-x86_64.o $(OBJS) -lgnuefi -lefi

all:
	make clean
	make build
	@ echo "target 'all' complete"

build: $(BUILDDIR)/kernel.efi
	@ echo "target 'build' complete"

clean:
	rm $(IMEDDIR)/* $(BUILDDIR)/*
	@ echo "target 'clean' complete"

$(BUILDDIR)/kernel.efi: $(BUILDDIR)/kernel.so
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym \
		-j .rel -j .rela -j .rel.* -j .rela.* -j .reloc \
		--target efi-app-x86_64 --subsystem=10 $^ $@

$(BUILDDIR)/kernel.so: $(OBJS)
	$(LD) $(LDFLAGS) -o $@

$(IMEDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
