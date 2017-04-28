
IS_CORE_FLAG := -DIS_CORE_CODE

E_LDF=bj-ld-script.ldf

PRU_SRC_DIR := .
PRU_INC_DIR := ../../ecore

MODULES_DIR := test/modules

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# ELIBS := -le-lib 
ELIBS :=

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := ${MODULES_DIR}/modules.elf

LD_FLAGS_1 := -static ${LD_IN_SECTIONS} 
TGT_LDFLAGS := -T ${E_LDF} --no-check-sections \
	-L${TARGET_DIR} -L${TARGET_DIR}/${MODULES_DIR} --strip-debug ${LD_FLAGS_1}

TGT_LDLIBS  := ${ELIBS} -lmod_1 -lmod_2 -lmod_3 -lbjk-actor 
TGT_PREREQS := \
	libbjk-actor.a \
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

SRC_CFLAGS := ${IS_CORE_FLAG} ${DBG_FLAG} ${STD_EPH_CFLAGS} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := ${IS_CORE_FLAG} ${DBG_FLAG} ${STD_EPH_CXXFLAGS} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(PRU_INC_DIR) 

SUBMAKEFILES := \
	common.mk \
	mod1.mk \
	mod2.mk \
	mod3.mk \

SOURCES := main_eph.cpp


