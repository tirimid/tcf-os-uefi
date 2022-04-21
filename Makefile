.ONESHELL:

BOOTDIR = boot
BBUILDDIR = $(BOOTDIR)/build
IMEDDIR = imed
BUILDDIR = build
OVMFDIR = ovmf

IMG = tcf-os-uefi.img

EMU = qemu-system-x86_64
EFLAGS = -cpu qemu64 -m 1G -net none \
	 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE.fd" \
	 -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS.fd"

all:
	make clean
	make run
	@ echo "target 'all' complete"

clean:
	cd $(BOOTDIR)
	make clean
	cd ..
	rm $(IMEDDIR)/* $(BUILDDIR)/*
	@ echo "target 'clean' complete"

build: $(BUILDDIR)/$(IMG)
	@ echo "target 'build' complete"

run: $(BUILDDIR)/$(IMG)
	$(EMU) $(EFLAGS) -drive file=$^
	@ echo "target 'run' complete"

$(BUILDDIR)/$(IMG): $(IMEDDIR)/BOOTX64.EFI
	dd if=/dev/zero of=$@ bs=1k count=1440
	mformat -i $@ -f 1440 ::
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $^ ::/EFI/BOOT

$(IMEDDIR)/BOOTX64.EFI: $(BBUILDDIR)/BOOTX64.EFI
	cp $^ $@

$(BBUILDDIR)/BOOTX64.EFI:
	cd $(BOOTDIR)
	make build
	cd ..
