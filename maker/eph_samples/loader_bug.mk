
IS_CORE_FLAG := -DIS_CORE_CODE

# FLG_1 := -L${ETOOLS}/e-gnu/epiphany-elf/lib
# FLG_2 := -L${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
# LIB_FLAGS_1 := ${FLG_1} ${FLG_2}

E_LDF=bj-ld-script.ldf
# E_LDF=eph_samples/mix_elfs/module.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

SRC_ECORE_DIR := ../${SRC_DIR}/ecore
PRU_SRC_DIR := ../${SRC_DIR}/test/loader_bug
PRU_INC_DIR := ${SRC_ECORE_DIR}

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# OPTSZ_FLAG := -Os # DOES NOT WORK WITH e-gcc ???? BAD GENERATED CODE ????
OPTSZ_FLAG := 

# STDLIBS := -lc -lepiphany -lgcc -lg 
STDLIBS := 

# ELIBS := -le-lib 
ELIBS :=

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := loader_bug.elf

LD_FLAGS_1 := -static ${LD_IN_SECTIONS} 
TGT_LDFLAGS := -T ${E_LDF} -L${TARGET_DIR} --strip-debug ${LD_FLAGS_1}

TGT_LDLIBS  := ${STDLIBS} ${ELIBS} -lbjk-actor
TGT_PREREQS := libbjk-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

SRC_CFLAGS := -DIS_CORE_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(PRU_INC_DIR) 

SOURCES := \
	$(PRU_SRC_DIR)/send_msg.cpp \
	$(PRU_SRC_DIR)/test_logs.c \
	$(PRU_SRC_DIR)/a_shd_code_error.cpp


