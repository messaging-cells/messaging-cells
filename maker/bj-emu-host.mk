
IS_EMU_FLAG := -DIS_EMU_CODE

SRC_HOST_DIR := $(SRC_DIR)/host

SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# =======================================

C_FLAGS_1 := -Wall -std=gnu11 -pthread
SRC_CFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${C_FLAGS_1}

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -pthread
SRC_CXXFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_ECORE_DIR}

SOURCES := \
	$(SRC_ECORE_DIR)/core_main_emu.c \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_emu.c 

