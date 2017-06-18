
H_DIR=${ESDK}/tools/host

H_LIB_1=${ETOOLS}/host/lib
H_INC_1=${ETOOLS}/host/include

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

TARGET := libmcz-cell.a

TGT_PREREQS := libmcz-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SUBMAKEFILES := mc-znq-host.mk mc-znq-cell-kernel.mk

