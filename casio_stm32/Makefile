# target
BUILD_DIR = build
TARGET = stm32_calculator

# Initialize compiler
TOOL_CHAIN_PATH = /home/biu/Workspace/Tools/gcc-arm-none-eabi-10.3-2021.10/bin
PREFIX = arm-none-eabi-

CC = $(TOOL_CHAIN_PATH)/$(PREFIX)gcc
AS = $(TOOL_CHAIN_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(TOOL_CHAIN_PATH)/$(PREFIX)objcopy
SZ = $(TOOL_CHAIN_PATH)/$(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# MCU Flags
CPU = -mcpu=cortex-m0
MCU_FLAGS = $(CPU) -mthumb -mfloat-abi=soft

# Sources
C_SOURCES = \
Core/Src/main.c \
Core/Src/LCD_driver.c \
Core/Src/keypad.c \
Core/Src/calculator_engine.c \
Core/Src/app_main.c \
Core/Startup/startup_stm32f030k6tx.c \
Drivers/gpio/gpio.c \
Drivers/clock/clock.c \
Drivers/clock/system_stm32_init.c 

C_INCLUDES = \
-ICore/Inc \
-IDrivers/clock \
-IDrivers/gpio 

# CFLAGS && LDFLAGS
OPT    = -Og -g -gdwarf-2
C_DEFS = -DSTM32F030x6
CFLAGS = $(MCU_FLAGS) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# Linker Script
LDSCRIPT = STM32F030K6TX_FLASH.ld
LDFLAGS  = $(MCU_FLAGS) -specs=nano.specs -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Rule Section
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo "Building finished successfully"

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "Compiling $<"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	@$(CP) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	@$(CP) -O binary -S $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
