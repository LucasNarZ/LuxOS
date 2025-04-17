KERNEL_BIN = kernel.bin
ISO_NAME = myos.iso

CC = gcc
LD = ld
CFLAGS = -ffreestanding -m32 -c
LDFLAGS = -T kernel/linker.ld -melf_i386

KERNEL_DIR = kernel
ISO_DIR = iso
GRUB_DIR = $(ISO_DIR)/boot/grub

all: $(ISO_NAME)

kernel.o: $(KERNEL_DIR)/kernel.c
	$(CC) $(CFLAGS) $< -o $@

gdt.o: $(KERNEL_DIR)/gdt.c
	$(CC) $(CFLAGS) $< -o $@

utils.o: $(KERNEL_DIR)/utils.c
	$(CC) $(CFLAGS) $< -o $@

boot.o: $(KERNEL_DIR)/boot.s
	nasm -f elf32 $< -o $@

$(KERNEL_BIN): boot.o kernel.o gdt.o utils.o
	$(LD) $(LDFLAGS) -o $@ $^

$(ISO_NAME): $(KERNEL_BIN)
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/
	echo 'menuentry "Kernel" {\n\tmultiboot /boot/$(KERNEL_BIN)\n\tboot\n}' > $(GRUB_DIR)/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

run: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME) -serial mon:stdio


clean:
	rm -f *.o $(KERNEL_BIN) $(ISO_NAME)
	rm -rf $(ISO_DIR)/boot
