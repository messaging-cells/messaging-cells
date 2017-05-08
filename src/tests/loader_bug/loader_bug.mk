
#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := loader_bug.elf

TGT_LDFLAGS := ${BJ_STD_EPH_LDFLAGS} ${LD_IN_SECTIONS} 
TGT_LDLIBS  := ${BJ_STD_EPH_LDLIBS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld
TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DIS_CORE_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := test_logs.c loader_bug.cpp


