KERNELDIR=kernel
BOOTDIR=boot
COMMONDIR=common
LIBCDIR=libc

echo "lines of code:"
cloc $KERNELDIR $BOOTDIR $COMMONDIR $LIBCDIR --quiet
