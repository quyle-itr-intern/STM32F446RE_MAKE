# Makefile Test Peripheral

PRO_DIR		:= .
PROJ_NAME	:= STM32F401CCU6_RTOS
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
INC_DIR		+= $(PRO_DIR)/driver/inc
SRC_DIR 	:= $(PRO_DIR)/src
SRC_DIR 	+= $(PRO_DIR)/driver/src

LINKER_FILE	:= $(PRO_DIR)/linker/STM32F401CCUx.ld

INC_FILES   := $(foreach INC_DIR, $(INC_DIR), $(wildcard  $(INC_DIR)/*))
SRC_FILES   := $(foreach SRC_DIR, $(SRC_DIR), $(wildcard  $(SRC_DIR)/*))

COMPILER_DIR 	:= E:/GNU_Arm_Embedded_Toolchain/10_2021.10
PREFIX_GCC_COMPILER	:= arm-none-eabi

CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

INCLUDE_DIRS_OPT := $(foreach INC_DIR,$(INC_DIR),-I$(INC_DIR))
# 							 -o0 -o1 -o2 -o3
CC_OPT			:= -mcpu=cortex-m4 -c -std=gnu11 -o0 -g -mthumb $(INCLUDE_DIRS_OPT)
ASM_OPT			:= -mcpu=cortex-m4 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map --print-memory-usage

OJB_FILES 	:= $(notdir $(SRC_FILES))
OJB_FILES 	:= $(subst .c,.o, $(OJB_FILES))
PATH_OJBS	:= $(foreach OJB_FILES, $(OJB_FILES), $(OUTPUT_PATH)/$(OJB_FILES))

vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

build: $(OJB_FILES) $(LINKER_FILE)
	@echo "Link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) $(PATH_OJBS) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf 
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex $(OUTPUT_PATH)/$(PROJ_NAME).elf $(OUTPUT_PATH)/$(PROJ_NAME).hex
	size $(OUTPUT_PATH)/$(PROJ_NAME).elf

%.o: %.c $(INC_FILES)
	mkdir -p $(OUTPUT_PATH)
	$(CC) $(CC_OPT) -c $< -o $(OUTPUT_PATH)/$@

.PHONY: flash
flash:
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -p $(OUTPUT_PATH)/$(PROJ_NAME).hex 0x08000000
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -rst	
	
.PHONY: report
report:
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -r32 0x20000000 0x04 | grep -i 00000000 > $(OUTPUT_PATH)/result.log; \
	if [[ -s $(OUTPUT_PATH)/result.log ]]; then \
		echo "Test $(TEST) PASS"; \
	else \
		echo "Test $(TEST) FAILED"; \
	fi \
	
.PHONY: clean
clean:
	@rm -rf $(OUTPUT_PATH)/*

.PHONY: info
info:
	
log-%:
	@echo $($(subst log-,,$@))