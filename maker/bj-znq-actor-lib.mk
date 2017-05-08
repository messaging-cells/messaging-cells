
H_DIR=${ESDK}/tools/host

H_LIB_1=${ETOOLS}/host/lib
H_INC_1=${ETOOLS}/host/include

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# =======================================

TARGET := libbjz-actor.a

# TARGET := bj-actor-booter.elf

TGT_LDFLAGS := -Ur -L${H_LIB_1} -L${TARGET_DIR}

TGT_LDLIBS  := -le-hal -le-loader -lm -lbjz-dlmalloc
TGT_PREREQS := libbjz-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++
TGT_LINKER := $(CROSS_COMPILE)gcc

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SUBMAKEFILES := bj-znq-host.mk bj-znq-actor-kernel.mk

