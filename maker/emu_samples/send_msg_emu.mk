
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
TGT_LDLIBS  := ${STDLIBS} -lbj-emu-actor -lpthread
TGT_PREREQS := libbj-emu-actor.a

C_FLAGS_1 := -Wall -std=gnu11 -nostdlib -fno-default-inline ${SRC_IN_SECTIONS}
SRC_CFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${C_FLAGS_1} -pthread

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables ${SRC_IN_SECTIONS}
CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
SRC_CXXFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2} -pthread

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) 

SOURCES := \
	$(PRU_SRC_DIR)/send_msg_emu.cpp \
	$(PRU_SRC_DIR)/send_msg.cpp \


