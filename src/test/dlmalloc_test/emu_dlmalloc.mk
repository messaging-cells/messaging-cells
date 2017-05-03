
IS_EMU_FLAG := -DIS_EMU_CODE

SRC_TEST_DIR := ./
SRC_HOST_DIR := ../../host
SRC_ECORE_DIR := ../../ecore

DBG_FLAG := -DFULL_DEBUG

# =======================================

TARGET := emu_dlmalloc_test.elf

TGT_LDFLAGS := -L${TARGET_DIR} 
TGT_LDLIBS  := -lbjm-tak-mak -lbjm-dlmalloc
TGT_PREREQS := libbjm-tak-mak.a libbjm-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

C_FLAGS_1 := -Wall -std=gnu11 -pthread
SRC_CFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${C_FLAGS_1}

CXX_FLAGS_1 := -Wall -std=c++14 -pthread
SRC_CXXFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := $(SRC_HOST_DIR) ${SRC_ECORE_DIR}

SOURCES := $(SRC_TEST_DIR)/dbg_dlmalloc.cpp



