
BJ_PTD_LIB_DIR := pthreads/lib/
BJ_PTD_BIN_DIR := pthreads/bin/
BJ_PTD_TGT_DIMACS := ${BJ_PTD_LIB_DIR}/libdimacs-ptd.a
BJ_PTD_TGT_BEN_JOSE := ${BJ_PTD_BIN_DIR}/ben-jose-embryo-ptd.elf

# MC_STD_PTD_LDFLAGS := -L${MC_LIB_DIR} -L${TARGET_DIR} -L${TARGET_DIR}/${BJ_PTD_LIB_DIR}
MC_STD_PTD_LDFLAGS := -L${MC_LIB_DIR} -L${TARGET_DIR}/${BJ_PTD_LIB_DIR}
MC_STD_PTD_LDLIBS := -lmcm-cell -lmcm-tak-mak -lmcm-dlmalloc -lpthread

# =======================================

TARGET := ${BJ_PTD_TGT_BEN_JOSE}

TGT_LDFLAGS := ${MC_STD_PTD_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${MC_STD_PTD_LDLIBS} -lstdc++ -ldimacs-ptd 
TGT_PREREQS := ${BJ_PTD_TGT_DIMACS}

CNFS_LNK_DIR := $(TARGET_DIR)/${BJ_PTD_BIN_DIR}
CNFS_LNK_DIR := $(call CANONICAL_PATH,${CNFS_LNK_DIR})

CNFS_LNK := ${CNFS_LNK_DIR}/cnfs
CNFS_LNK := $(call CANONICAL_PATH,${CNFS_LNK})

define POST_OPERS
	if [ ! -e $(CNFS_LNK) ]; then ln -s ${CNFS_DIR} ${CNFS_LNK_DIR}; fi;
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

C_FLAGS_1 := -Wall -std=gnu11 -g3 -pthread 
SRC_CFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${C_FLAGS_1} 

CXX_FLAGS_1 := -Wall -std=c++14 -g3 -pthread 
SRC_CXXFLAGS := -DMC_IS_PTD_CODE ${MC_DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := ${BJ_MANAGERU_INCLUDES}

SUBMAKEFILES := ./lib-dimacs-ptd.mk ./all_modules_ptd.mk 

SOURCES := ${SRC_BJ_MANAGERU_DIR}/bj_manageru_code.cpp 






