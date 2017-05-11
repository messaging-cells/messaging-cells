
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ACTORS_DIR := $(SRC_DIR)/actors

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# =======================================

C_FLAGS_1 := -Wall -std=gnu11 -pthread
SRC_CFLAGS := -DBJ_IS_EMU_CODE ${DBG_FLAG} ${C_FLAGS_1}

CXX_FLAGS_1 := -Wall -std=c++14 -pthread
SRC_CXXFLAGS := -DBJ_IS_EMU_CODE ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_ACTORS_DIR}

#	$(SRC_HOST_DIR)/booter_emu.cpp 

 SOURCES := \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_emu.cpp \
	$(SRC_HOST_DIR)/thread_emu.cpp



