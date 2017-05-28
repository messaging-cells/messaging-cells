
#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := philo_emu.elf

TGT_LDFLAGS := ${BJ_STD_EMU_LDFLAGS} ${LD_IN_SECTIONS} -rdynamic
TGT_LDLIBS  := ${BJ_STD_EMU_LDLIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DBJ_IS_EMU_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS} -g3 -pthread
SRC_CXXFLAGS := -DBJ_IS_EMU_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS} -g3 -pthread

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := philo.cpp ../nil_host/nil_host.cpp


