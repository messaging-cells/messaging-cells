
TARGET := hola_jose_emu.elf

TGT_LDFLAGS := ${MC_STD_EMU_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${MC_STD_EMU_LDLIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CFLAGS} ${MC_DBG_FLAG} -pthread
SRC_CXXFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CXXFLAGS} ${MC_DBG_FLAG} -pthread

SRC_INCDIRS := ${MC_STD_INCDIRS}

SOURCES := hola_jose.cpp 


