# This special target sets the behavior of make to conform to the POSIX standard.
# When .POSIX is declared, make operates in a mode that is more strictly compliant
# with the POSIX standard, which can affect how certain features and behaviors work,
# aiming for portability and standard compliance across different systems.
.POSIX:

# This special target is used to declare that the targets that follow it are not actual
# files. Instead, they are "phony" targets, which means they are always considered 
# out-of-date and will always be executed when specified. This is useful for targets 
# like `all` and `clean`, which are not real files but rather commands or groups of commands 
# that you want to run. Declaring them as `.PHONY` ensures that `make` does not confuse them 
# with actual files of the same name and always executes their recipes when they are the
# target of `make`.
.PHONY: all clean

# Verbosity control
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
Q =
else
Q = @
endif

# Directory for output UEFI files
OUTPUT_DIRECTORY = build

# Find all .c files in the examples directory
SOURCES= $(wildcard ./examples/*.c)

# Convert the list of source files (.c) into target EFI files (.EFI) in the OUTPUT_DIRECTORY
TARGETS = $(patsubst ./examples/%.c,./$(OUTPUT_DIRECTORY)/%.efi,$(SOURCES))

# Default example to be compiled if no target is specified
EXAMPLE ?= $(OUTPUT_DIRECTORY)/uefi-hello-world.efi

# Compiler settings (Uncomment the one you're using)
# 	Specifies the subsystem under which the executable operates. In this case, it's the Windows subsystem.
# 	Specifies the entry point for the executable. In this case, it's the efi_main function.
# 	Specifies the maximum number of errors to display before stopping compilation.
# 	Generates debugging information in the executable file.
CC = x86_64-w64-mingw32-gcc \
	-Wl,--subsystem,10 \
	-e efi_main \
	-fmax-errors=5 \
	-g

# CC = clang \
	-target x86_64-unknown-windows \
	-fuse-ld=lld-link \
	-Wl,-subsystem:efi_application \
	-Wl,-entry:efi_main

# Specifies the C standard to use for compilation. In this case, it's C17, the ISO/IEC 9899:2018 standard
# Enables all the warnings about constructions that some users consider questionable, and that are easy to avoid.
# Enables some extra warning flags that are not enabled by -Wall.
# Makes all warnings into errors. Compilation will stop if any warnings are encountered.
# Issues all the warnings demanded by strict ISO C; rejects all programs that use forbidden extensions, and some other programs that do not follow ISO C.
# Asserts that compilation is for a freestanding environment, which is one where standard library functions may not exist, and program startup may not necessarily be at main.
# Tells the compiler not to use the standard system startup files or libraries when linking. It's useful for compiling code that does not rely on any standard library functions.
CFLAGS = \
	-std=c17 \
	-Wall \
	-Wextra \
	-Werror \
	-Wpedantic \
	-mno-red-zone \
	-ffreestanding \
	-nostdlib

info :
	@echo "SOURCES: $(SOURCES)"
	@echo "TARGETS: $(TARGETS)"
	@echo "EXAMPLE: $(EXAMPLE)"

# Rule to make all targets
all: info $(OUTPUT_DIRECTORY) $(TARGETS)

# Target to create the output directory
$(OUTPUT_DIRECTORY):
	@echo "Creating $(OUTPUT_DIRECTORY) directory"
	$(Q)mkdir -p $(OUTPUT_DIRECTORY)

# Pattern rule for building EFI files from C files
$(OUTPUT_DIRECTORY)/%.efi: ./examples/%.c
	@echo "Compiling $< into $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $<

# Target to generate the GPT disk image
generate-image:
	@echo "Generating GPT disk image"
	$(Q)cp ./$(EXAMPLE) ./UEFI-GPT-image-creator/BOOTX64.EFI
	$(Q)cd UEFI-GPT-image-creator && ./write_gpt

# Target to run the example
run-example: all generate-image $(EXAMPLE) 
	@echo "Running $(EXAMPLE)"
	$(Q)@qemu-system-x86_64 -drive format=raw,file=./UEFI-GPT-image-creator/test.hdd -bios /usr/share/OVMF/OVMF-pure-efi.fd -name TESTOS -machine q35 -net none

debug-example: all generate-image $(EXAMPLE) 
	@echo "Running $(EXAMPLE)"
	$(Q)@qemu-system-x86_64 -drive format=raw,file=./UEFI-GPT-image-creator/test.hdd -bios /usr/share/OVMF/OVMF-pure-efi.fd -name TESTOS -machine q35 -net none -S -s


clean:
	@echo "Cleaning up $(OUTPUT_DIRECTORY) directory"
	$(Q)rm -rf $(OUTPUT_DIRECTORY)


