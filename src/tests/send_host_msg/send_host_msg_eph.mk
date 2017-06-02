
#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := send_host_msg_eph.elf

TGT_LDFLAGS := ${BJ_STD_EPH_LDFLAGS} ${LD_IN_SECTIONS} 
TGT_LDLIBS  := ${BJ_STD_EPH_LDLIBS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld

define POST_OPERS
	e-objdump -D $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET).s
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

SRC_CFLAGS := -DBJ_IS_EPH_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DBJ_IS_EPH_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := send_host_msg.cpp


