
E_LDF=bj-ld-script.ldf

PRU_SRC_DIR := .
PRU_INC_DIR := ../../ecore
OBJ_DIR := .

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

STDLIBS := -lc -lepiphany -lgcc -lg 
# STDLIBS := 

LFLAG_1 := -L${ETOOLS}/e-gnu/epiphany-elf/lib
LFLAG_2 := -L${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/

OBJ_LFLAGS := ${LFLAG_1} ${LFLAG_2}
# OBJ_LFLAGS := 

# =======================================

TARGET := ${OBJ_DIR}/test_tak_mak.elf

TGT_LDFLAGS := -T ${E_LDF} -L${TARGET_DIR} ${OBJ_LFLAGS} --strip-debug -static ${LD_IN_SECTIONS} 
TGT_LDLIBS  := -lbjk-actor -lbjk-tak-mak ${STDLIBS}
TGT_PREREQS := libbjk-actor.a libbjk-tak-mak.a

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld
TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DIS_CORE_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(PRU_INC_DIR) 

SOURCES := $(PRU_SRC_DIR)/test_tak_mak.cpp


