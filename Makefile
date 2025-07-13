# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Flags
CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -ffreestanding -Wall
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections

# Sources
SRC_C = main.c startup.c

# Object files
OBJ_C = $(SRC_C:.c=.o)
OBJ = $(OBJ_C) $(OBJ_S)

# Outputs
ELF = main.elf
BIN = main.bin
PRE = main.i
ASM = main.s

# Default target
all: $(BIN)

# Preprocess main.c
$(PRE): $(SRC_C)
	$(CC) $(CFLAGS) -E $< -o $@

# Generate assembly from main.c
$(ASM): $(SRC_C)
	$(CC) $(CFLAGS) -S $< -o $@

# Compile C source files to object files
$(OBJ_C): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly source files to object files
$(OBJ_S): %.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into an ELF executable
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Convert ELF to binary
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Run with QEMU
run: $(BIN)
	qemu-system-arm -M stm32-p103 -nographic -kernel $(BIN)

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(ELF) $(BIN) $(ASM) $(PRE)

