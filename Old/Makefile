# sharing basic makefile

PRO_DIR		:= .
PROJ_NAME	:= 01-STM32F446RE_GPIO
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
SRC_DIR 	:= $(PRO_DIR)/src
LINKER_FILE	:= $(PRO_DIR)/linker/STM32F446RETx.ld

COMPILER_DIR 	:= E:/GNU Arm Embedded Toolchain/10 2021.10
PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_stm32f446xx.o

CC_OPT			:= -mcpu=cortex-m4 -c -std=gnu11 -o0 -g -mthumb -I$(INC_DIR)
ASM_OPT			:= -mcpu=cortex-m4 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/startup_stm32f446xx.o: $(SRC_DIR)/startup_stm32f446xx.S
	@echo "compile $(SRC_DIR)/startup_stm32f446xx.S file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_stm32f446xx.s -o $(OUTPUT_PATH)/startup_stm32f446xx.o

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf 
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(OUTPUT_PATH)/$(PROJ_NAME).elf" "$(OUTPUT_PATH)/$(PROJ_NAME).hex"
	size $(OUTPUT_PATH)/$(PROJ_NAME).elf
clean:
	@rm -rf $(OUTPUT_PATH)/*


# PRO_DIR		:= .
# PROJ_NAME	:= 01-STM32F446RE_GPIO
# OUTPUT_PATH := $(PRO_DIR)/output

# INC_DIR		:= $(PRO_DIR)/inc
# SRC_DIR 	:= $(PRO_DIR)/src
# LINKER_FILE	:= $(PRO_DIR)/linker/STM32F446RETx.ld

# INC_FILES   := $(foreach INC_DIR, $(INC_DIR), $(wildcard  $(INC_DIR)/*))
# SRC_FILES   := $(foreach SRC_DIR, $(SRC_DIR), $(wildcard  $(SRC_DIR)/*))

# COMPILER_DIR 	:= E:/GNU Arm Embedded Toolchain/10 2021.10
# PREFIX_GCC_COMPILER	:= arm-none-eabi

# CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
# ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
# LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

# FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_stm32f446xx.o

# CC_OPT			:= -mcpu=cortex-m4 -c -std=gnu11 -o0 -g -mthumb -I$(INC_DIR)
# ASM_OPT			:= -mcpu=cortex-m4 -c -mthumb
# LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

# OJB_FILES 	:= $(notdir $(SRC_FILES))
# OJB_FILES 	:= $(subst .c,.o, $(OJB_FILES))
# PATH_OJBS	:= $(foreach OJB_FILES, $(OJB_FILES), $(OUTPUT_PATH)/$(OJB_FILES))

# vpath %.c $(SRC_DIR)
# vpath %.h $(INC_DIR)

# $(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
# 	@echo "compile $(SRC_DIR)/main.c file"
# 	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

# $(OUTPUT_PATH)/startup_stm32f446xx.o: $(SRC_DIR)/startup_stm32f446xx.S
# 	@echo "compile $(SRC_DIR)/startup_stm32f446xx.S file"
# 	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_stm32f446xx.s -o $(OUTPUT_PATH)/startup_stm32f446xx.o

# build: $(FILE_TO_LINK) $(LINKER_FILE)
# 	@echo "link object files to create new binary image ($(PROJ_NAME).elf)"
# 	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf 
# 	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(OUTPUT_PATH)/$(PROJ_NAME).elf" "$(OUTPUT_PATH)/$(PROJ_NAME).hex"
# 	size $(OUTPUT_PATH)/$(PROJ_NAME).elf

# .PYTHON: clean
# clean:
# 	@rm -rf $(OUTPUT_PATH)/*