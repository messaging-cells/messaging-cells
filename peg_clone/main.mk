
BUILD_DIR := ./build
TARGET_DIR := ./

HL_CURR_DIR := $(shell pwd)

C_BASE_FLAGS := -Wall -std=gnu11
CXX_BASE_FLAGS := -Wall -std=c++17

BMETAL_CFLAGS := ${C_BASE_FLAGS} -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

BMETAL_CXXFLAGS_P1 := -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
BMETAL_CXXFLAGS_P2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BMETAL_CXXFLAGS := ${CXX_BASE_FLAGS} ${BMETAL_CXXFLAGS_P1} ${BMETAL_CXXFLAGS_P2}

SG_DBG_FLAG := -DFULL_DEBUG

SG_BASE_DIR := ./src_peg

# -------------------------------------------------------------------------------------------


TARGET := peg_clone

TGT_LDFLAGS := -rdynamic -pthread

TGT_LDLIBS := -lgmpxx -lgmp

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := ${C_BASE_FLAGS} ${SG_DBG_FLAG} -pthread
SRC_CXXFLAGS := ${CXX_BASE_FLAGS} ${SG_DBG_FLAG} -pthread

SRC_INCDIRS := ${SG_BASE_DIR}

SOURCES := \
	${SG_BASE_DIR}/compile.c \
	${SG_BASE_DIR}/peg.c \
	${SG_BASE_DIR}/tree.c \


