
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

TARGET := min-host.elf

TGT_LDFLAGS := ${MC_STD_ZNQ_LDFLAGS}
TGT_LDLIBS  := ${MC_STD_ZNQ_LDLIBS}

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=gnu11 ${MC_DBG_FLAG}
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=c++14 ${MC_DBG_FLAG}

SRC_INCDIRS := $(MC_STD_INCDIRS)

SOURCES := min_host.cpp
