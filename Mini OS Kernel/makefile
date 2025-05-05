# Makefile for mini OS kernel

# Compiler and linker settings
CC = gcc
LD = ld
AS = nasm
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -m32
LDFLAGS = -T scripts/linker.ld -m elf_i386
ASFLAGS = -f elf32

# Directories
SRC_DIR = kernel
BOOT_DIR = boot
LIB_DIR = lib
DRIVERS_DIR = drivers
FS_DIR = fs
BUILD_DIR = build

# Files
KERNEL_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/memory.c $(SRC_DIR)/process.c $(SRC_DIR)/vga.c $(SRC_DIR)/terminal.c
LIB_SRC = $(LIB_DIR)/string.c
DRIVERS_SRC = $(DRIVERS_DIR)/keyboard.c
FS_SRC = $(FS_DIR)/fs.c
BOOT_SRC = $(BOOT_DIR)/boot.asm

OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

KERNEL_OBJ = $(OBJ_DIR)/kernel.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/process.o $(OBJ_DIR)/vga.o $(OBJ_DIR)/terminal.o
LIB_OBJ = $(OBJ_DIR)/string.o
DRIVERS_OBJ = $(OBJ_DIR)/keyboard.o
FS_OBJ = $(OBJ_DIR)/fs.o
BOOT_OBJ = $(OBJ_DIR)/boot.o

KERNEL_BIN = $(BIN_DIR)/kernel.bin
BOOT_BIN = $(BIN_DIR)/boot.bin
ISO = $(BIN_DIR)/mini_os.iso

# Targets
all: $(ISO)

# Assemble bootloader
$(OBJ_DIR)/boot.o: $(BOOT_DIR)/boot.asm
	$(AS) $(ASFLAGS) -o $@ $<

# Compile kernel, drivers, and library
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(SRC_DIR) -I$(DRIVERS_DIR) -I$(FS_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c -o $@ $<

# Link the kernel
$(KERNEL_BIN): $(KERNEL_OBJ) $(LIB_OBJ) $(DRIVERS_OBJ) $(FS_OBJ) $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Create ISO
$(ISO): $(BOOT_BIN) $(KERNEL_BIN)
	mkdir -p $(BIN_DIR)/iso/boot/grub
	cp $(KERNEL_BIN) $(BIN_DIR)/iso/boot/kernel.bin
	cp $(BOOT_BIN) $(BIN_DIR)/iso/boot/boot.bin
	cp $(BOOT_DIR)/grub.cfg $(BIN_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BIN_DIR)/iso

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create necessary directories
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@
