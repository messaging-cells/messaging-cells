
# H_INC_1=${ETOOLS}/host/include

SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

TARGET := libmck-cell.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc
TGT_CXX := e-g++

SRC_CFLAGS := -DMC_IS_EPH_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DMC_IS_EPH_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_CELLS_DIR) 

#	$(SRC_CELLS_DIR)/link_syms_struct_eph.c \

SOURCES := \
	$(SRC_CELLS_DIR)/interruptions_eph.c \
	$(SRC_CELLS_DIR)/umm_malloc.c \
	$(SRC_CELLS_DIR)/umm_malloc_eph.c \
	$(SRC_CELLS_DIR)/log.c \
	$(SRC_CELLS_DIR)/shared.c \
	$(SRC_CELLS_DIR)/shared_eph.c \
	$(SRC_CELLS_DIR)/loader_eph.c \
	$(SRC_CELLS_DIR)/broadcast_maps_eph.c \
	$(SRC_CELLS_DIR)/err_msgs.c \
	$(SRC_CELLS_DIR)/global.c \
	$(SRC_CELLS_DIR)/global_eph.c \
	$(SRC_CELLS_DIR)/rr_array.c \
	$(SRC_CELLS_DIR)/trace_eph.c \
	$(SRC_CELLS_DIR)/e_start.s \
	$(SRC_CELLS_DIR)/dyn_mem.c \
	$(SRC_CELLS_DIR)/call_cores_main_eph.c \
	$(SRC_CELLS_DIR)/binder.cpp \
	$(SRC_CELLS_DIR)/cell_eph.cpp \
	$(SRC_CELLS_DIR)/cell.cpp \


