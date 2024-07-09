.POSIX:
.PHONY: all clean

SOURCE = uefi.c
TARGET = BOOTX64.EFI

# Uncomment for gcc
CC = x86_64-w64-mingw32-gcc \
	-Wl,--subsystem,10 \
	-e efi_main \
	-fmax-errors=50 
	-g

# Uncomment for clang
# CC = clang \
	-target x86_64-unknown-windows \
	-fuse-ld=lld-link \
	-Wl,-subsystem:efi_application \
	-Wl,-entry:efi_main

CFLAGS = \
	-std=c17 \
	-Wall \
	-Wextra \
	-Werror \
	-Wpedantic \
	-mno-red-zone \
	-ffreestanding \
	-nostdlib 

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<
	cp $(TARGET) ./UEFI-GPT-image-creator/

clean:
	rm -rf $(TARGET)
