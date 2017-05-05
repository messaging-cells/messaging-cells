

# =======================================

SRC_CFLAGS := -DIS_ZNQ_CODE -Wall -std=gnu11 ${DBG_FLAG}
SRC_CXXFLAGS := -DIS_ZNQ_CODE -Wall -std=c++14 ${DBG_FLAG}

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) $(H_INC_1) 

SOURCES := \
	$(SRC_ECORE_DIR)/rr_array.c \
	$(SRC_ECORE_DIR)/shared_znq.cpp \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_HOST_DIR)/core_loader_znq.c \
	$(SRC_HOST_DIR)/prt_eph_call_stack_znq.c \
	$(SRC_HOST_DIR)/read_eph_elf_link_syms_tab_znq.c \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/booter_znq.cpp \


