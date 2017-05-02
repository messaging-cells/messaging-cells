
SRC_ECORE_DIR := $(SRC_DIR)/ecore

HCOMP=$(CROSS_COMPILE)gcc

# =======================================

DEF_FLAGS_1 := -DUSE_TSD_DATA_HACK -D_REENTRANT -DTHREAD_STATS=1 
DEF_FLAGS_2 := -DONLY_MSPACES -DUSE_LOCKS=0 -DHAVE_MMAP=0 -DHAVE_MREMAP=0 

TARGET := libbjz-tak-mak.a

TGT_CC := $(HCOMP)

TGT_LINKER := $(HCOMP)

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -Wall -std=gnu11 -g -O2 -Wstrict-prototypes $(DEF_FLAGS_1) $(DEF_FLAGS_2)

SOURCES := $(SRC_ECORE_DIR)/tak_mak.cpp 


