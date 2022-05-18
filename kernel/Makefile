# ----- directories -----

LIBC_DIR = ../libc
IMED_DIR = imed
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build

# ----- compilation -----

CC = clang
CFLAGS = -target x86_64-elf -std=c11 -pedantic -I$(INC_DIR) -ffreestanding -I../inc \
	 -I$(LIBC_DIR)/inc -mno-red-zone

AS = x86_64-elf-as
ASFLAGS =

LD = clang
LDS = linker.ld
LDFLAGS = -ffreestanding -nostdlib -T$(LDS) -Bsymbolic -static

# ----- objects -----

LIBC_SOURCES = $(shell find $(LIBC_DIR)/src -name *.c)
LIBC_OBJS = $(patsubst $(LIBC_DIR)/src/%.c, $(IMED_DIR)/%.c.o, $(LIBC_SOURCES))
SOURCES = $(shell find $(SRC_DIR) -name *.c -or -name *.s)
OBJS = $(patsubst $(SRC_DIR)/%, $(IMED_DIR)/%, $(addsuffix .o, $(SOURCES)))

ALL_SOURCES = $(LIBC_SOURCES) $(SOURCES)
ALL_OBJS = $(LIBC_OBJS) $(OBJS)

# ----- output -----

ELF = kernel.elf

# ----- targets -----

all: clean build
	@ echo "target 'all' complete"

clean:
	rm -r $(BUILD_DIR)/* $(IMED_DIR)/*
	@ echo "target 'clean' complete"

build: $(BUILD_DIR)/$(ELF)
	@ echo "target 'build' complete"

$(BUILD_DIR)/$(ELF): $(ALL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMED_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $@
	rmdir $@
	$(CC) $(CFLAGS) -o $@ -c $^

$(IMED_DIR)/%.s.o: $(SRC_DIR)/%.s
	mkdir -p $@
	rmdir $@
	$(AS) $(ASFLAGS) -o $@ $^

$(IMED_DIR)/int/%.c.o: $(SRC_DIR)/int/%.c
	mkdir -p $@
	rmdir $@
	$(CC) $(CFLAGS) -o $@ -c $^ -mgeneral-regs-only

$(IMED_DIR)/%.c.o: $(LIBC_DIR)/src/%.c
	mkdir -p $@
	rmdir $@
	$(CC) $(CFLAGS) -o $@ -c $^
