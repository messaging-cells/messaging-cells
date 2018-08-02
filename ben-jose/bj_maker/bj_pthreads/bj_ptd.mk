
# =======================================

TARGET := ben-jose-ptd.elf

TGT_LDFLAGS := ${MC_STD_PTD_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${MC_STD_PTD_LDLIBS} -lstdc++ -ldimacs-ptd 
TGT_PREREQS := ${MC_PTD_LIBS} libdimacs-ptd.a 

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

C_FLAGS_1 := -Wall -std=gnu11 -g3 -pthread 
SRC_CFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${C_FLAGS_1} 

CXX_FLAGS_1 := -Wall -std=c++14 -g3 -pthread 
SRC_CXXFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := ${BJ_MANAGERU_INCLUDES}

SUBMAKEFILES := ./lib-dimacs-ptd.mk ./all_modules_ptd.mk 

SOURCES := ${SRC_BJ_MANAGERU_DIR}/bj_manageru_code.cpp 






