
SRC_ACTORS_DIR := $(SRC_DIR)/actors

# =======================================

TARGET := libbjk-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc
TGT_CXX := e-g++

SRC_CFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_ACTORS_DIR) 

SOURCES := \
	$(SRC_ACTORS_DIR)/interruptions.c \
	$(SRC_ACTORS_DIR)/umm_malloc.c \
	$(SRC_ACTORS_DIR)/umm_malloc_eph.c \
	$(SRC_ACTORS_DIR)/link_syms_struct_eph.c \
	$(SRC_ACTORS_DIR)/log.c \
	$(SRC_ACTORS_DIR)/shared.c \
	$(SRC_ACTORS_DIR)/shared_eph.c \
	$(SRC_ACTORS_DIR)/err_msgs.c \
	$(SRC_ACTORS_DIR)/global.c \
	$(SRC_ACTORS_DIR)/global_eph.c \
	$(SRC_ACTORS_DIR)/rr_array.c \
	$(SRC_ACTORS_DIR)/trace_eph.c \
	$(SRC_ACTORS_DIR)/e_start.s \
	$(SRC_ACTORS_DIR)/dyn_mem.c \
	$(SRC_ACTORS_DIR)/call_bj_cores_main_eph.c \
	$(SRC_ACTORS_DIR)/binder.cpp \
	$(SRC_ACTORS_DIR)/actor_eph.cpp \
	$(SRC_ACTORS_DIR)/actor.cpp \


