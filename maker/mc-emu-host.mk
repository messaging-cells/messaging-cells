
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

C_FLAGS_1 := -Wall -std=gnu11 ${g_FLAG} -pthread 
SRC_CFLAGS := -DMC_IS_EMU_CODE ${DBG_FLAG} ${C_FLAGS_1} 

CXX_FLAGS_1 := -Wall -std=c++14 ${g_FLAG} -pthread 
SRC_CXXFLAGS := -DMC_IS_EMU_CODE ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_CELLS_DIR}

#	$(SRC_HOST_DIR)/booter_emu.cpp 

 SOURCES := \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_emu.cpp \
	$(SRC_HOST_DIR)/thread_emu.cpp



