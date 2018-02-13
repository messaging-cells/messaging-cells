
IS_EMU_FLAG := -DMC_IS_EMU_CODE

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_CELLS_DIR := $(SRC_DIR)/cells

# =======================================

SRC_CFLAGS := -DMC_IS_EMU_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${g_FLAG} -pthread 
SRC_CXXFLAGS := -DMC_IS_EMU_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${g_FLAG} -pthread 

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_CELLS_DIR) 

SOURCES := \
	$(SRC_CELLS_DIR)/umm_malloc.c \
	$(SRC_CELLS_DIR)/umm_malloc_emu.cpp \
	$(SRC_CELLS_DIR)/log.c \
	$(SRC_CELLS_DIR)/shared.c \
	$(SRC_CELLS_DIR)/shared_emu.cpp \
	$(SRC_CELLS_DIR)/global.c \
	$(SRC_CELLS_DIR)/global_emu.cpp \
	$(SRC_CELLS_DIR)/broadcast_maps.c \
	$(SRC_CELLS_DIR)/loader_emu.cpp \
	$(SRC_CELLS_DIR)/rr_array.c \
	$(SRC_CELLS_DIR)/trace_emu.cpp \
	$(SRC_CELLS_DIR)/dyn_mem_emu.cpp \
	$(SRC_CELLS_DIR)/dyn_mem.c \
	$(SRC_CELLS_DIR)/binder.cpp \
	$(SRC_CELLS_DIR)/cell.cpp \
	$(SRC_CELLS_DIR)/cell_emu.cpp 

