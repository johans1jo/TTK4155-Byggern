FAMILY := nrf51
SOURCES := main.c uart.c twi.c utility.c accel.c
SOURCES += ubit_led_matrix.c

BUILD_DIR := .build_system
LINKER_SCRIPT := $(BUILD_DIR)/linker_script.ld

GNU_PREFIX	:= arm-none-eabi
CC			:= $(GNU_PREFIX)-gcc
OBJCOPY		:= $(GNU_PREFIX)-objcopy
OBJDUMP		:= $(GNU_PREFIX)-objdump

QUIET := @

## Compiler flags
# CPU specific
CFLAGS += -mcpu=cortex-m0 -mthumb -mabi=aapcs -mfloat-abi=soft
# Get linker optimization for free
CFLAGS += -ffunction-sections -fdata-sections --short-enums
CFLAGS += -fno-strict-aliasing -fno-builtin
# Good pracice
CFLAGS += -Wall -Werror -std=gnu99 -g3
# CFLAGS += -ggdb -Og / -O0 / -O3 etc

## Linker flags
CFLAGS += --specs=nosys.specs -Wl,--gc-sections -T $(LINKER_SCRIPT)
# or --specs=nano.specs -lc -lnosys

SOURCES += $(BUILD_DIR)/system_nrf51.c
SOURCES += $(BUILD_DIR)/gcc_startup_nrf51.S

.PHONY: default flash clean

default:
	@echo Compiling project
	$(QUIET)$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/main.elf
	@echo Creating hex file
	$(QUIET)$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

flash:
	nrfjprog -f $(FAMILY) --sectorerase --program $(BUILD_DIR)/main.hex
	nrfjprog -f $(FAMILY) --reset

erase:
	nrfjprog -f $(FAMILY) --eraseall

clean:
	$(QUIET)rm $(BUILD_DIR)/main.{elf,hex}
