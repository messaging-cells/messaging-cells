
H_DIR=${ESDK}/tools/host

H_LIB_1=${ETOOLS}/host/lib
H_INC_1=${ETOOLS}/host/include

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ACTORS_DIR := $(SRC_DIR)/actors

# =======================================

TARGET := libbjz-actor.a

TGT_PREREQS := libbjz-dlmalloc.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := $(CROSS_COMPILE)gcc
TGT_CXX := $(CROSS_COMPILE)g++

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SUBMAKEFILES := bj-znq-host.mk bj-znq-actor-kernel.mk

