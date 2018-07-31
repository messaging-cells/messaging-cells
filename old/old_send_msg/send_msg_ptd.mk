
#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := send_msg_ptd.elf

TGT_LDFLAGS := ${MC_STD_PTD_LDFLAGS} ${LD_IN_SECTIONS} -rdynamic
TGT_LDLIBS  := ${MC_STD_PTD_LDLIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := -DMC_IS_PTD_CODE ${MC_STD_EPH_CFLAGS} ${MC_DBG_FLAG} ${SRC_IN_SECTIONS} -pthread
SRC_CXXFLAGS := -DMC_IS_PTD_CODE ${MC_STD_EPH_CXXFLAGS} ${MC_DBG_FLAG} ${SRC_IN_SECTIONS} -pthread

SRC_INCDIRS := ${MC_STD_INCDIRS}

SOURCES := send_msg.cpp ../nil_host/nil_host.cpp


