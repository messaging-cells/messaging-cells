
BUILD_DIR := ./build
TARGET_DIR := ./

HL_CURR_DIR := $(shell pwd)

C_BASE_FLAGS := -Wall -std=gnu11
CXX_BASE_FLAGS := -Wall -std=c++17

BMETAL_CFLAGS := ${C_BASE_FLAGS} -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

BMETAL_CXXFLAGS_P1 := -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
BMETAL_CXXFLAGS_P2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BMETAL_CXXFLAGS := ${CXX_BASE_FLAGS} ${BMETAL_CXXFLAGS_P1} ${BMETAL_CXXFLAGS_P2}

VL_DBG_FLAG := -DFULL_DEBUG

VL_BASE_DIR := ./src_vpp

# -------------------------------------------------------------------------------------------


TARGET := vpp_lang

TGT_LDFLAGS := -rdynamic -pthread

TGT_LDLIBS := -lgmpxx -lgmp

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := ${C_BASE_FLAGS} ${VL_DBG_FLAG} -pthread
SRC_CXXFLAGS := ${CXX_BASE_FLAGS} ${VL_DBG_FLAG} -pthread

SRC_INCDIRS := ${VL_BASE_DIR}

SOURCES := \
	${VL_BASE_DIR}/test_lexis.cpp \


# -------------------------------------------------------------------------------------------
# Needed rules

.PHONY: First_Rule
First_Rule : all

${VL_BASE_DIR}/test_lexis.cpp : ${VL_BASE_DIR}/peg_output.c


${VL_BASE_DIR}/peg_output.c : peg_clone/peg_clone ${VL_BASE_DIR}/vpp.peg
	peg_clone/peg_clone -o ${VL_BASE_DIR}/peg_output.c ${VL_BASE_DIR}/vpp.peg
	
peg_clone/peg_clone : 
	cd peg_clone; $(MAKE)

