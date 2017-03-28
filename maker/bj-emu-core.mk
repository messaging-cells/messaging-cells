
IS_EMU_FLAG := -DIS_EMU_CODE

# E_LDF := -T bj-ld-script.ldf
# ELDF := -T ${ESDK}/bsps/current/fast.ldf
E_LDF := 

SRC_HOST_DIR := $(SRC_DIR)/host

SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# STDLIBS := -lc -lepiphany -lgcc -lg 
STDLIBS := 

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

C_FLAGS_1 := -Wall -std=gnu11 -nostdlib -fno-default-inline ${SRC_IN_SECTIONS}
SRC_CFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${C_FLAGS_1} -pthread

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables ${SRC_IN_SECTIONS}
CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
SRC_CXXFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2} -pthread

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) 

#	$(SRC_ECORE_DIR)/test_logs.c \
#	$(SRC_ECORE_DIR)/umm_malloc.c \
#	$(SRC_ECORE_DIR)/dyn_mem.cpp \
#	$(SRC_ECORE_DIR)/actor.cpp \
#	$(SRC_ECORE_DIR)/std2.c \

#	$(SRC_ECORE_DIR)/interruptions.c \
#	$(SRC_ECORE_DIR)/umm_malloc.c \
#	$(SRC_ECORE_DIR)/log.c \
#	$(SRC_ECORE_DIR)/shared.c \
#	$(SRC_ECORE_DIR)/global.c \
#	$(SRC_ECORE_DIR)/rr_array.c \
#	$(SRC_ECORE_DIR)/trace.c \
#	$(SRC_ECORE_DIR)/dyn_mem.cpp \
#	$(SRC_ECORE_DIR)/binder.cpp \
#	$(SRC_ECORE_DIR)/actor.cpp 

SOURCES := \
	$(SRC_ECORE_DIR)/umm_malloc.c \
	$(SRC_ECORE_DIR)/umm_malloc_emu.cpp \
	$(SRC_ECORE_DIR)/log.c \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_ECORE_DIR)/shared_emu.cpp \
	$(SRC_ECORE_DIR)/global.c \
	$(SRC_ECORE_DIR)/global_emu.cpp \
	$(SRC_ECORE_DIR)/rr_array.c \
	$(SRC_ECORE_DIR)/trace_emu.cpp \
	$(SRC_ECORE_DIR)/test_logs.c \
	$(SRC_ECORE_DIR)/a_shd_code_error.cpp \
	$(SRC_ECORE_DIR)/dyn_mem.cpp \
	$(SRC_ECORE_DIR)/binder.cpp \
	$(SRC_ECORE_DIR)/actor.cpp \
	$(SRC_ECORE_DIR)/actor_emu.cpp 

