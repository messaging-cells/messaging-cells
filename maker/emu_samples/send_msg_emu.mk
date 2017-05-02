
PRU_SRC_DIR := ../${SRC_DIR}/test/send_msg
PRU_INC_DIR := ../${SRC_DIR}/ecore


IS_EMU_FLAG := -DIS_EMU_CODE

# E_LDF := -T bj-ld-script.ldf
# ELDF := -T ${ESDK}/bsps/current/fast.ldf
E_LDF := 

SRC_HOST_DIR := ../$(SRC_DIR)/host

SRC_ECORE_DIR := ../$(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# STDLIBS := -lc -lepiphany -lgcc -lg 
STDLIBS := 

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := send_msg_emu.elf

TGT_LDFLAGS := -L${TARGET_DIR} 
TGT_LDLIBS  := ${STDLIBS} -lbjm-actor -lbjm-tak-mak -lpthread
TGT_PREREQS := libbjm-actor.a libbjm-tak-mak.a

SRC_CFLAGS := -DIS_EMU_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_EMU_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) 

SOURCES := \
	$(PRU_SRC_DIR)/send_msg_emu.cpp \
	$(PRU_SRC_DIR)/send_msg.cpp \


