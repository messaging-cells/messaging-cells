
IS_CORE_FLAG := -DIS_CORE_CODE

E_LDF=${SRC_DIR}/test/modules/module.ldf

PRU_SRC_DIR := .
PRU_INC_DIR := ../../ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# ELIBS := -le-lib 
ELIBS :=

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := test/modules/libmod_1.a

LD_FLAGS_1 := -static ${LD_IN_SECTIONS} 
TGT_LDFLAGS := -T ${E_LDF} -L${TARGET_DIR} --strip-debug ${LD_FLAGS_1}

TGT_LDLIBS  := ${ELIBS} -lbjk-actor
TGT_PREREQS := libbjk-actor.a libcommon.a

define POST_OPERS
	../src/test/modules/mod_make_redef_list.sh $(TARGET_DIR)/$(TARGET) m1
	../src/test/modules/mod_repl_common_syms.sh $(TARGET_DIR)/$(TARGET) m1 module1_code module1_data
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld

SRC_CFLAGS := ${IS_CORE_FLAG} ${DBG_FLAG} ${STD_EPH_CFLAGS} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := ${IS_CORE_FLAG} ${DBG_FLAG} ${STD_EPH_CXXFLAGS} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(PRU_INC_DIR) 

SOURCES := \
	$(PRU_SRC_DIR)/common.cpp \
	$(PRU_SRC_DIR)/pru_1.cpp


