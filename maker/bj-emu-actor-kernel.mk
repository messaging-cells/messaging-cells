
IS_EMU_FLAG := -DBJ_IS_EMU_CODE

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ACTORS_DIR := $(SRC_DIR)/actors

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# =======================================

SRC_CFLAGS := -DBJ_IS_EMU_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} -pthread 
SRC_CXXFLAGS := -DBJ_IS_EMU_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} -pthread 

# C_FLAGS_1 := -Wall -std=gnu11 -nostdlib -fno-default-inline ${SRC_IN_SECTIONS}
# SRC_CFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${C_FLAGS_1} -pthread

# CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables ${SRC_IN_SECTIONS}
# CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
# SRC_CXXFLAGS := ${IS_EMU_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2} -pthread

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ACTORS_DIR) 

SOURCES := \
	$(SRC_ACTORS_DIR)/umm_malloc.c \
	$(SRC_ACTORS_DIR)/umm_malloc_emu.cpp \
	$(SRC_ACTORS_DIR)/log.c \
	$(SRC_ACTORS_DIR)/shared.c \
	$(SRC_ACTORS_DIR)/shared_emu.cpp \
	$(SRC_ACTORS_DIR)/err_msgs.c \
	$(SRC_ACTORS_DIR)/global.c \
	$(SRC_ACTORS_DIR)/global_emu.cpp \
	$(SRC_ACTORS_DIR)/rr_array.c \
	$(SRC_ACTORS_DIR)/trace_emu.cpp \
	$(SRC_ACTORS_DIR)/dyn_mem_emu.cpp \
	$(SRC_ACTORS_DIR)/dyn_mem.c \
	$(SRC_ACTORS_DIR)/binder.cpp \
	$(SRC_ACTORS_DIR)/actor.cpp \
	$(SRC_ACTORS_DIR)/actor_emu.cpp 

