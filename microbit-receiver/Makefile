# List all source files to be compiled; separate with space
SOURCE_FILES := main.c ubit.c bluetooth.c

# Feel free to ignore anything below this line
FAMILY := nrf51

BUILD_DIR := build
LINKER_SCRIPT := $(BUILD_DIR)/linker_script.ld

SOFTDEVICE_ROOT := softdevice
SOFTDEVICE_API := $(SOFTDEVICE_ROOT)/s130_nrf51_2.0.1_API/include
SOFTDEVICE_HEX := $(SOFTDEVICE_ROOT)/s130_nrf51_2.0.1_softdevice.hex

OBJECT_FILES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
OBJECT_FILES += $(BUILD_DIR)/gcc_startup_nrf51.o
OBJECT_FILES += $(BUILD_DIR)/system_nrf51.o

GNU_PREFIX	:= arm-none-eabi
CC			:= $(GNU_PREFIX)-gcc
OBJCOPY		:= $(GNU_PREFIX)-objcopy
OBJDUMP		:= $(GNU_PREFIX)-objdump

CFLAGS += -mcpu=cortex-m0 -mthumb -mabi=aapcs -mfloat-abi=soft
CFLAGS += -ffunction-sections -fdata-sections --short-enums
CFLAGS += -fno-strict-aliasing -fno-builtin
CFLAGS += -Wall -Werror -std=gnu99
CFLAGS += -I$(SOFTDEVICE_API)

LFLAGS := --specs=nosys.specs -Wl,--gc-sections -T $(LINKER_SCRIPT)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR)/gcc_startup_nrf51.o: $(BUILD_DIR)/gcc_startup_nrf51.S
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/system_nrf51.o: $(BUILD_DIR)/system_nrf51.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/nosoft.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/nosoft.elf $(BUILD_DIR)/nosoft.hex
	mergehex -m $(SOFTDEVICE_HEX) $(BUILD_DIR)/nosoft.hex -o $@

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	nrfjprog -f $(FAMILY) --chiperase --program $(BUILD_DIR)/main.hex
	nrfjprog -f $(FAMILY) --reset

.PHONY: erase
erase:
	nrfjprog -f $(FAMILY) --eraseall

.PHONY: clean
clean:
	rm $(OBJECT_FILES)
	rm $(BUILD_DIR)/nosoft.{elf,hex}
	rm $(BUILD_DIR)/main.hex
