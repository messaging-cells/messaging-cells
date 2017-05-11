
# DIR_ELIBS_1=${ETOOLS}/e-gnu/epiphany-elf/lib
DIR_ELIBS_1 := 
# DIR_ELIBS_2=${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
DIR_ELIBS_2 := 

E_LDF=bj-ld-script.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

SRC_ACTORS_DIR := $(SRC_DIR)/actors

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

TARGET := libbjk-tak-mak.a

LD_FLAGS_1 := -static
TGT_LDFLAGS := -T ${E_LDF} -Ur -L${DIR_ELIBS_1} -L${DIR_ELIBS_2} --strip-debug ${LD_IN_SECTIONS} ${LD_FLAGS_1}

TGT_LDLIBS  := ${STDLIBS} ${ELIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

SRC_CFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_ACTORS_DIR) 

SOURCES := $(SRC_ACTORS_DIR)/tak_mak.cpp 

