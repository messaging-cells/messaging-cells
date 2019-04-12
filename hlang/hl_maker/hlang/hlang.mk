
HLANG_BASE_DIR := ${HL_CURR_DIR}/../hl_src

BMETAL_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

BMETAL_CXXFLAGS_P1 := -Wall -std=c++17 -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
BMETAL_CXXFLAGS_P2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BMETAL_CXXFLAGS := ${BMETAL_CXXFLAGS_P1} ${BMETAL_CXXFLAGS_P2}

HLANG_BMETAL_CFLAGS := ${BMETAL_CFLAGS} 
HLANG_BMETAL_CXXFLAGS := ${BMETAL_CXXFLAGS} 

HLANG_DBG_FLAG := -DFULL_DEBUG

SRC_HLANG_LIB_DIR := hlang
HLANG_LIB_DIR := hlang/lib/
HLANG_BIN_DIR := hlang/bin/

HLANG_LIB_INCLUDES := \
	${HLANG_BASE_DIR}/ \
	${HLANG_BASE_DIR}/hl_util \
	${HLANG_BASE_DIR}/hl_test \


HLANG_TESTS_LDFLAGS := -L${TARGET_DIR}/${HLANG_LIB_DIR}
HLANG_TESTS_LDLIBS := -lhlang 

# =======================================

TARGET := ${HLANG_BIN_DIR}/hlang_tests.elf

TGT_LDFLAGS := ${HLANG_TESTS_LDFLAGS} -rdynamic
TGT_LDLIBS  := ${HLANG_TESTS_LDLIBS} -lstdc++ 
TGT_PREREQS := ${HLANG_LIB_DIR}/libhlang.a

define POST_OPERS
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
	pwd
	cd $(TARGET_DIR)/${HLANG_BIN_DIR}; ./hlang_tests.elf
	pwd
	#./hlang_tests.elf
	printf "====================================\nFinished generating cpp code \n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

C_FLAGS_1 := -Wall -std=gnu11 -g3 -pthread 
SRC_CFLAGS := ${HLANG_DBG_FLAG} ${C_FLAGS_1} 

CXX_FLAGS_1 := -Wall -std=c++17 -g3 -pthread 
SRC_CXXFLAGS := ${HLANG_DBG_FLAG} ${CXX_FLAGS_1}

SRC_INCDIRS := ${HLANG_LIB_INCLUDES}

SUBMAKEFILES := ./lib-hlang.mk ./htests.mk 

SOURCES := \
	${HLANG_BASE_DIR}/hl_test/hl_tests.cpp \






