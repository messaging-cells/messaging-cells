
MODULES_DIR := modules

TARGET := ${MODULES_DIR}/modules.elf

TGT_LDFLAGS := ${BJ_STD_EPH_LDFLAGS} ${LD_IN_SECTIONS} --no-check-sections -L${TARGET_DIR}/${MODULES_DIR}
TGT_LDLIBS  := -lmod_1 -lmod_2 -lmod_3 ${BJ_STD_EPH_LDLIBS}

TGT_PREREQS := \
	${MODULES_DIR}/libcommon.a \
	${MODULES_DIR}/libmod_1.a \
	${MODULES_DIR}/libmod_2.a \
	${MODULES_DIR}/libmod_3.a \


define POST_OPERS
	e-objdump -D $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET).s
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld

SRC_CFLAGS := -DBJ_IS_EPH_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DBJ_IS_EPH_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SUBMAKEFILES := \
	common.mk \
	mod1.mk \
	mod2.mk \
	mod3.mk \

SOURCES := main_eph.cpp


