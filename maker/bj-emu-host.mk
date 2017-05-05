
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# =======================================

C_FLAGS_1 := -Wall -std=gnu11 -pthread
SRC_CFLAGS := -DIS_EMU_CODE ${DBG_FLAG} ${C_FLAGS_1}

CXX_FLAGS_1 := -Wall -std=c++14 -pthread
SRC_CXXFLAGS := -DIS_EMU_CODE ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_ECORE_DIR}

#	$(SRC_HOST_DIR)/booter_emu.cpp 

 SOURCES := \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_emu.cpp \
	$(SRC_HOST_DIR)/thread_emu.cpp



