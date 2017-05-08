
#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := test_dlmalloc_emu.elf

TGT_LDFLAGS := ${BJ_STD_EMU_LDFLAGS} ${LD_IN_SECTIONS} 
TGT_LDLIBS  := ${BJ_STD_EMU_LDLIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DIS_EMU_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS} -pthread
SRC_CXXFLAGS := -DIS_EMU_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS} -pthread

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := test_dlmalloc.cpp 


