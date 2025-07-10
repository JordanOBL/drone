# Makefile for STM32F103 simulation in QEMU
# Toolchain Prefix
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -ffreestanding -Wall
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections

# Files
SRC = main.c
PRE = main.i
ASM = main.s
OBJ = main.o
ELF = main.elf
BIN = main.bin

all: $(PRE) $(ASM) $(OBJ) $(ELF) $(BIN)

# Preprocessing: expands includes and macros
$(PRE): $(SRC)
	$(CC) $(CFLAGS) -E $< -o $@

# Compilation to assembly
$(ASM): $(SRC)
	$(CC) $(CFLAGS) -S $< -o $@

# Compilation to object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Linking to produce ELF
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Binary file for flash
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

#Preprocess return '.i' (expand C #includes #headers into full paths within .c file)
preprocess:
	$(CC) -E $(SRC) -o $(PRE)
# Clean up
clean:
	rm -f $(PRE) $(ASM) $(OBJ) $(ELF) $(BIN)

# Run with QEMU
run: $(BIN)
	qemu-system-arm -M stm32-p103 -nographic -kernel $(BIN)

