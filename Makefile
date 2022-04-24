.ONESHELL:

BOOTDIR = boot
BBUILDDIR = $(BOOTDIR)/build
KERNELDIR = kernel
KBUILDDIR = $(KERNELDIR)/build
IMEDDIR = imed
BUILDDIR = build
OVMFDIR = ovmf
OSFILESDIR = os-files

KERNELELF = tcf-kernel.elf
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
	cd ../$(KERNELDIR)
	make clean
	cd ..
	rm $(IMEDDIR)/* $(BUILDDIR)/*
	@ echo "target 'clean' complete"

build: $(BUILDDIR)/$(IMG)
	@ echo "target 'build' complete"

run: $(BUILDDIR)/$(IMG)
	$(EMU) $(EFLAGS) -drive file=$^
	@ echo "target 'run' complete"

# writes necessary OS files to disk image which has only UEFI stuff currently
$(BUILDDIR)/$(IMG): $(IMEDDIR)/$(IMG) $(IMEDDIR)/$(KERNELELF)
	cp $< $@
	mmd -i $@ ::/sys
	mcopy -i $@ $(OSFILESDIR)/sys/sys.cfg ::/sys
	mcopy -i $@ $(IMEDDIR)/$(KERNELELF) ::/sys
	mmd -i $@ ::/uefi
	mcopy -i $@ $(OSFILESDIR)/uefi/test.txt ::/uefi

$(IMEDDIR)/$(IMG): $(IMEDDIR)/BOOTX64.EFI
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

$(IMEDDIR)/$(KERNELELF): $(KBUILDDIR)/$(KERNELELF)
	cp $^ $@

$(KBUILDDIR)/$(KERNELELF):
	cd $(KERNELDIR)
	make build
	cd ..
