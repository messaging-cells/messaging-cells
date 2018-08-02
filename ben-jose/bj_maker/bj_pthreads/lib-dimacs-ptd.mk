
TARGET := libdimacs-ptd.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

# SRC_CFLAGS := -Wall -std=gnu11 -O2 -Wstrict-prototypes 

SRC_CFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=gnu11 ${MC_DBG_FLAG}
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE -Wall -std=c++14 ${MC_DBG_FLAG}

SOURCES := \
	$(SRC_BJ_MANAGERU_DIR)/utils/bj_mem.cpp \
	$(SRC_BJ_MANAGERU_DIR)/utils/bj_stream.cpp \
	$(SRC_BJ_MANAGERU_DIR)/utils/stack_trace.cpp \
	$(SRC_BJ_MANAGERU_DIR)/utils/top_exception.cpp \
	$(SRC_BJ_MANAGERU_DIR)/utils/parse_funcs.cpp \
	$(SRC_BJ_MANAGERU_DIR)/utils/file_funcs.cpp \
	$(SRC_BJ_MANAGERU_DIR)/dimacs/dimacs.cpp \

SRC_INCDIRS := \
	$(SRC_BJ_MANAGERU_DIR)/dimacs \
	$(SRC_BJ_MANAGERU_DIR)/utils 


