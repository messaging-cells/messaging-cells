
IS_EMU_FLAG := -DMC_IS_EMU_CODE

SRC_TEST_DIR := ./
SRC_HOST_DIR := ../../host
SRC_CELLS_DIR := ../../cells

DBG_FLAG := -DFULL_DEBUG

# =======================================

TARGET := znq_dlmalloc_test.elf

TGT_LDFLAGS := -L${TARGET_DIR} 
TGT_LDLIBS  := -lmcz-tak-mak -lmcz-dlmalloc
TGT_PREREQS := libmcz-tak-mak.a libmcz-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

C_FLAGS_1 := -Wall -std=gnu11 -pthread
SRC_CFLAGS := -DMC_IS_ZNQ_CODE ${DBG_FLAG} ${C_FLAGS_1}

CXX_FLAGS_1 := -Wall -std=c++14 -pthread
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_CELLS_DIR}

SOURCES := $(SRC_TEST_DIR)/dbg_dlmalloc.cpp



