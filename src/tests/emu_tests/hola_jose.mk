
TARGET := hola_jose_emu.elf

TGT_LDFLAGS := ${BJ_STD_EMU_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${BJ_STD_EMU_LDLIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DBJ_IS_EMU_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} -pthread
SRC_CXXFLAGS := -DBJ_IS_EMU_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} -pthread

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := hola_jose.cpp 


