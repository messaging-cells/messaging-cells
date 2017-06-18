

# =======================================

SRC_CFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=gnu11 ${DBG_FLAG}
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=c++14 ${DBG_FLAG}

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_CELLS_DIR) $(H_INC_1) 

SOURCES := \
	$(SRC_CELLS_DIR)/rr_array.c \
	$(SRC_CELLS_DIR)/shared_znq.cpp \
	$(SRC_CELLS_DIR)/shared.c \
	$(SRC_HOST_DIR)/core_loader_znq.c \
	$(SRC_HOST_DIR)/prt_eph_call_stack_znq.c \
	$(SRC_HOST_DIR)/read_eph_elf_link_syms_tab_znq.c \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_znq.cpp \


