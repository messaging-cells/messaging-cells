
TARGET := test_addr_conv.elf

TGT_LDFLAGS := ${BJ_STD_ZNQ_LDFLAGS}
TGT_LDLIBS  := ${BJ_STD_ZNQ_LDLIBS}

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DBJ_IS_ZNQ_CODE -Wall -std=gnu11 ${BJ_DBG_FLAG}
SRC_CXXFLAGS := -DBJ_IS_ZNQ_CODE -Wall -std=c++14 ${BJ_DBG_FLAG}

SRC_INCDIRS := $(BJ_STD_INCDIRS)

SOURCES := addr_conv.cpp
