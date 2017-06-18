
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

TARGET := znq_backtrace.elf

TGT_LDFLAGS := ${MC_STD_ZNQ_LDFLAGS} -rdynamic 
TGT_LDLIBS  := ${MC_STD_ZNQ_LDLIBS}

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=gnu11 ${MC_DBG_FLAG} -g -fno-omit-frame-pointer
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=c++14 ${MC_DBG_FLAG} -g 

SRC_INCDIRS := $(MC_STD_INCDIRS)

# znq_getfp.s 

SOURCES := znq_backtrace.c
