
SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells
SRC_BJ_HOST_DIR := .

# =======================================

TARGET := host_code.elf

TGT_LDFLAGS := ${MC_STD_ZNQ_LDFLAGS}
TGT_LDLIBS  := ${MC_STD_ZNQ_LDLIBS} -lstdc++ -ldimacs 
TGT_PREREQS := ${MC_ZNQ_LIBS} libdimacs.a 
# TGT_LDLIBS  := ${MC_STD_ZNQ_LDLIBS} 
# TGT_PREREQS := ${MC_ZNQ_LIBS} 


TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)g++

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=gnu11 ${MC_DBG_FLAG}
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=c++14 ${MC_DBG_FLAG}

SRC_INCDIRS := \
	$(MC_STD_INCDIRS) \
	$(SRC_BJ_HOST_DIR)/dimacs \
	$(SRC_BJ_HOST_DIR)/utils 

SUBMAKEFILES := ./lib-dimacs.mk 

SOURCES := host_code.cpp
