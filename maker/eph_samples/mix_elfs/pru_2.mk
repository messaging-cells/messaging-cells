
IS_CORE_FLAG := -DIS_CORE_CODE

# FLG_1 := -L${ETOOLS}/e-gnu/epiphany-elf/lib
# FLG_2 := -L${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
# LIB_FLAGS_1 := ${FLG_1} ${FLG_2}

E_LDF=eph_samples/mix_elfs/module.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

PRU_SRC_DIR := ../../${SRC_DIR}/test/pru_mix_link
PRU_INC_DIR := ../../${SRC_DIR}/ecore

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

TARGET := eph_pru_2.elf

LD_FLAGS_1 := -static ${LD_IN_SECTIONS} 
TGT_LDFLAGS := -T ${E_LDF} -L${TARGET_DIR} --strip-debug ${LD_FLAGS_1}

TGT_LDLIBS  := ${STDLIBS} ${ELIBS} -lbjk-actor
TGT_PREREQS := libbjk-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

# -Wall -std=c11 -nostdlib -nostartfiles
C_FLAGS_1 := -ffreestanding -Wall -std=gnu11 -nostdlib -nostartfiles -fno-default-inline ${SRC_IN_SECTIONS}
SRC_CFLAGS := ${IS_CORE_FLAG} ${OPTSZ_FLAG} ${DBG_FLAG} ${C_FLAGS_1}

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables ${SRC_IN_SECTIONS}
CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
SRC_CXXFLAGS := ${IS_CORE_FLAG} ${OPTSZ_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2}

SRC_INCDIRS := $(PRU_INC_DIR) 

SOURCES := \
	$(PRU_SRC_DIR)/main_eph_2.c \
	$(PRU_SRC_DIR)/pru_2.cpp


