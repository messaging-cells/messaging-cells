
HLANG_BIN_DIR := hlang/bin/
MCELLS_DIR := ../cells
MCELLS_PTD_LIB_DIR := cell_libs

GCPP_TESTS_BASE_DIR := ${HL_CURR_DIR}/hl_install/hlang/bin/hl_generated_output_cpp
MC_TESTS_BASE_DIR := ${HL_CURR_DIR}/../hl_src/hl_test/mc_code

GCPP_TESTS_LIB_DIR := gcpp_tests/lib/
GCPP_TESTS_BIN_DIR := gcpp_tests/bin/

GCPP_TESTS_DBG_FLAG := -DFULL_DEBUG

BMETAL_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

BMETAL_CXXFLAGS_P1 := -Wall -std=c++17 -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
BMETAL_CXXFLAGS_P2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BMETAL_CXXFLAGS := ${BMETAL_CXXFLAGS_P1} ${BMETAL_CXXFLAGS_P2}

MC_ESDK=${EPIPHANY_HOME}
MC_ETOOLS=${MC_ESDK}/tools
MC_STD_INCDIRS := ${MCELLS_DIR} ${MCELLS_DIR}/manageru ${MC_ETOOLS}/host/include 

MC_STD_PTD_LDFLAGS := -L${MCELLS_PTD_LIB_DIR} -L${TARGET_DIR} 

MC_STD_PTD_LDLIBS := -lmc-ptd-cell -lmc-ptd-tak-mak -lmc-ptd-dlmalloc -lpthread

# =======================================

# TARGET := ${GCPP_TESTS_LIB_DIR}/libgcpp_tests.a
TARGET := ${GCPP_TESTS_BIN_DIR}/gcpp-tests-ptd.elf

TGT_LDFLAGS := ${MC_STD_PTD_LDFLAGS} ${LD_IN_SECTIONS} -rdynamic
TGT_LDLIBS  := ${MC_STD_PTD_LDLIBS}
# TGT_PREREQS := ${HLANG_BIN_DIR}/hlang_tests.elf

SRC_CFLAGS := -DMC_IS_PTD_CODE ${BMETAL_CFLAGS} ${GCPP_TESTS_DBG_FLAG} 
SRC_CXXFLAGS := -DMC_IS_PTD_CODE ${BMETAL_CXXFLAGS} ${GCPP_TESTS_DBG_FLAG} 

SRC_INCDIRS := ${MC_STD_INCDIRS} ${GCPP_TESTS_BASE_DIR}

SOURCES := \
	${GCPP_TESTS_BASE_DIR}/hl_generated_output_glbs.cpp \
	${GCPP_TESTS_BASE_DIR}/cls_snd.cpp \
	${MC_TESTS_BASE_DIR}/tests_mgru.cpp \
	${MC_TESTS_BASE_DIR}/tests_wrku.cpp \




