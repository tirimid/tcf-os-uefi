# ----- directories -----

GNU_EFI_DIR = ../gnu-efi
LIBC_DIR = ../libc
IMED_DIR = imed
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build

# ----- compilation -----

CC = clang
CFLAGS = -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone \
	 -I$(GNU_EFI_DIR)/inc -I$(GNU_EFI_DIR)/inc/x86_64 -I$(GNU_EFI_DIR)/inc/protocol \
	 -I$(INC_DIR) -std=c11 -pedantic -I../inc -I$(LIBC_DIR)/inc

LD = clang
LDFLAGS = -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main \
	  -Wl,-subsystem:efi_application -fuse-ld=lld-link

# ----- objects -----

LIBC_OBJS = $(IMED_DIR)/lcstring.c.o
SOURCES = $(shell find $(SRC_DIR) -name *.c -or -name *.s)
OBJS = $(patsubst $(SRC_DIR)/%, $(IMED_DIR)/%, $(addsuffix .o, $(SOURCES)))

ALL_SOURCES = $(LIBC_SOURCES) $(SOURCES)
ALL_OBJS = $(LIBC_OBJS) $(OBJS) $(IMED_DIR)/gnu-efi-data.c.o

# ----- targets -----

all: clean build
	@ echo "target 'all' complete"

clean:
	rm -r $(IMED_DIR)/* $(BUILD_DIR)/*
	@ echo "target 'clean' complete"

build: $(BUILD_DIR)/BOOTX64.EFI
	@ echo "target 'build' complete"

$(BUILD_DIR)/BOOTX64.EFI: $(ALL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMED_DIR)/gnu-efi-data.c.o: $(GNU_EFI_DIR)/lib/data.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMED_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $@
	rmdir $@
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMED_DIR)/%.c.o: $(LIBC_DIR)/src/%.c
	mkdir -p $@
	rmdir $@
	$(CC) $(CFLAGS) -o $@ -c $^
