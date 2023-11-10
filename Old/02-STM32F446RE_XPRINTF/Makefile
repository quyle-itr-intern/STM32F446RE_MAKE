# Makefile 01-STM32F446RE_XPRINTF

PRO_DIR		:= .
PROJ_NAME	:= 01-STM32F446RE_XPRINTF
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIRS	:= $(PRO_DIR)/inc
INC_DIRS	+= $(PRO_DIR)/common/inc
INC_DIRS	+= $(PRO_DIR)/std/inc
SRC_DIRS 	:= $(PRO_DIR)/src
SRC_DIRS 	+= $(PRO_DIR)/common/src
SRC_DIRS 	+= $(PRO_DIR)/std/src
LINKER_FILE	:= $(PRO_DIR)/linker/STM32F446RETx.ld

INC_FILES   := $(foreach INC_DIRS, $(INC_DIRS), $(wildcard  $(INC_DIRS)/*))
SRC_FILES   := $(foreach SRC_DIRS, $(SRC_DIRS), $(wildcard  $(SRC_DIRS)/*))

COMPILER_DIR 	:= E:/GNU_Arm_Embedded_Toolchain/10_2021.10
PREFIX_GCC_COMPILER	:= arm-none-eabi

CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

INCLUDE_DIRS_OPT := $(foreach INC_DIRS,$(INC_DIRS),-I$(INC_DIRS))

CC_OPT			:= -mcpu=cortex-m4 -c -std=gnu11 -o0 -g -mthumb $(INCLUDE_DIRS_OPT)
ASM_OPT			:= -mcpu=cortex-m4 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map --print-memory-usage

OJB_FILES 	:= $(notdir $(SRC_FILES))
OJB_FILES 	:= $(subst .c,.o, $(OJB_FILES))
PATH_OJBS	:= $(foreach OJB_FILES, $(OJB_FILES), $(OUTPUT_PATH)/$(OJB_FILES))

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)

build: $(OJB_FILES) $(LINKER_FILE)
	@echo "Link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) $(PATH_OJBS) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf 
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex $(OUTPUT_PATH)/$(PROJ_NAME).elf $(OUTPUT_PATH)/$(PROJ_NAME).hex
	size $(OUTPUT_PATH)/$(PROJ_NAME).elf

%.o: %.c $(INC_FILES)
	$(CC) $(CC_OPT) $< -o $(OUTPUT_PATH)/$@

.PHONY: flash
flash:
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -p $(OUTPUT_PATH)/$(PROJ_NAME).hex 0x08000000
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -rst	
	
.PHONY: report
report:
	$(PRO_DIR)/ST-LINK_Utility/ST-LINK_CLI.exe -r32 0x20000000 0x04 | grep -i 00000000 > $(OUTPUT_PATH)/result.log; \
	if [[ -s $(OUTPUT_PATH)/result.log ]]; then \
		echo "Test $(PROJ_NAME) PASS"; \
	else \
		echo "Test $(PROJ_NAME) FAILED"; \
	fi \
	
.PHONY: clean
clean:
	@rm -rf $(OUTPUT_PATH)/*
