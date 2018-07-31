
SRC_BJ_HOST_DIR := .

# =======================================

TARGET := ben-jose-ptd.elf

TGT_LDFLAGS := ${MC_STD_EMU_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${MC_STD_EMU_LDLIBS} -lstdc++ -ldimacs-emu 
TGT_PREREQS := ${MC_EMU_LIBS} libdimacs-emu.a 

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

C_FLAGS_1 := -Wall -std=gnu11 -g3 -pthread 
SRC_CFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${C_FLAGS_1} 

CXX_FLAGS_1 := -Wall -std=c++14 -g3 -pthread 
SRC_CXXFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := ${BJ_HOST_INCLUDES}

SUBMAKEFILES := ./lib-dimacs-ptd.mk ./all_modules_ptd.mk 

SOURCES := \
	../host_code/bj_host_code.cpp \






