
E_LDF=bj-ld-script.ldf
# E_LDF=eph_samples/mix_elfs/module.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

PRU_SRC_DIR := ../${SRC_DIR}/test/hello_world
PRU_INC_DIR := ../${SRC_DIR}/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# STDLIBS := -lc -lepiphany -lgcc -lg 
STDLIBS := 

# ELIBS := -le-lib 
ELIBS :=

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := hello_world.elf

TGT_LDFLAGS := -T ${E_LDF} -L${TARGET_DIR} --strip-debug -static ${LD_IN_SECTIONS} 
TGT_LDLIBS  := ${STDLIBS} ${ELIBS} -lbjk-actor
TGT_PREREQS := libbjk-actor.a

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld
TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DIS_CORE_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(PRU_INC_DIR) 

SOURCES := $(PRU_SRC_DIR)/hello_world.cpp


