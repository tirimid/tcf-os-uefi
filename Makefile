.ONESHELL:

BOOT_DIR = boot
B_BUILD_DIR = $(BOOT_DIR)/build
KERNEL_DIR = kernel
K_BUILD_DIR = $(KERNEL_DIR)/build
IMED_DIR = imed
BUILD_DIR = build
OVMF_DIR = ovmf
OS_FILES_DIR = os-files

KERNEL_ELF = kernel.elf
IMG = tcf-os-uefi.img

EMU = qemu-system-x86_64
EFLAGS = -cpu qemu64 -m 2G -net none \
	 -drive if=pflash,format=raw,unit=0,file="$(OVMF_DIR)/OVMF_CODE.fd" \
	 -drive if=pflash,format=raw,unit=1,file="$(OVMF_DIR)/OVMF_VARS.fd"

all: clean run
	@ echo "target 'all' complete"

clean:
	cd $(BOOT_DIR)
	make clean
	cd ../$(KERNEL_DIR)
	make clean
	cd ..
	rm -r $(IMED_DIR)/* $(BUILD_DIR)/*
	@ echo "target 'clean' complete"

build: $(BUILD_DIR)/$(IMG)
	@ echo "target 'build' complete"

run: $(BUILD_DIR)/$(IMG)
	$(EMU) $(EFLAGS) -drive file=$^
	@ echo "target 'run' complete"

# writes necessary OS files to disk image which has only UEFI stuff currently
$(BUILD_DIR)/$(IMG): $(IMED_DIR)/$(IMG) $(IMED_DIR)/$(KERNEL_ELF)
	cp $< $@
	mmd -i $@ ::/sys
	mcopy -i $@ $(OS_FILES_DIR)/sys/sys.cfg ::/sys
	mcopy -i $@ $(IMED_DIR)/$(KERNEL_ELF) ::/sys
	mcopy -i $@ $(OS_FILES_DIR)/sys/tamsyn-8x16-bold.psf ::/sys
	mmd -i $@ ::/uefi
	mcopy -i $@ $(OS_FILES_DIR)/uefi/test.txt ::/uefi

$(IMED_DIR)/$(IMG): $(IMED_DIR)/BOOTX64.EFI
	dd if=/dev/zero of=$@ bs=1k count=1440
	mformat -i $@ -f 1440 ::
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $^ ::/EFI/BOOT

$(IMED_DIR)/BOOTX64.EFI: $(B_BUILD_DIR)/BOOTX64.EFI
	cp $^ $@

$(B_BUILD_DIR)/BOOTX64.EFI:
	cd $(BOOT_DIR)
	make build
	cd ..

$(IMED_DIR)/$(KERNEL_ELF): $(K_BUILD_DIR)/$(KERNEL_ELF)
	cp $^ $@

$(K_BUILD_DIR)/$(KERNEL_ELF):
	cd $(KERNEL_DIR)
	make build
	cd ..
