KERNEL_DIR=kernel
BOOT_DIR=boot
INC_DIR=inc
LIBC_DIR=libc

echo "lines of code:"
cloc $KERNEL_DIR $BOOT_DIR $INC_DIR $LIBC_DIR --quiet
