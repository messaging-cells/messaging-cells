
IS_ZNQ_FLAG := -DIS_ZNQ_CODE

H_DIR=${ESDK}/tools/host

H_LIB_1=${ETOOLS}/host/lib
H_INC_1=${ETOOLS}/host/include

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 


# =======================================

TARGET := bj-actor-booter.elf

TGT_LDFLAGS := -Ur -L${H_LIB_1} -L${TARGET_DIR}

TGT_LDLIBS  := -le-hal -le-loader -lm -lbjz-dlmalloc
TGT_PREREQS := libbjz-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

SRC_CFLAGS := -Wall -std=gnu11 ${DBG_FLAG} ${IS_ZNQ_FLAG} 
SRC_CXXFLAGS := -Wall -std=c++14 ${DBG_FLAG} ${IS_ZNQ_FLAG} 

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) $(H_INC_1) 

SOURCES := \
	$(SRC_ECORE_DIR)/rr_array.c \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_HOST_DIR)/core_loader_znq.c \
	$(SRC_HOST_DIR)/prt_eph_call_stack_znq.c \
	$(SRC_HOST_DIR)/read_eph_elf_link_syms_tab_znq.c \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_znq.cpp \


