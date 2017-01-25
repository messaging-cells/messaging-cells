
E_LIBS_1=${ETOOLS}/e-gnu/epiphany-elf/lib
E_LIBS_2=${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/

E_LDF=bj-ld-script.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG

# OPTSZ_FLAG := -Os # DOES NOT WORK WITH e-gcc ???? BAD GENERATED CODE ????
OPTSZ_FLAG := 

# =======================================

TARGET := e_$(NAME_PRG).elf

TGT_LDFLAGS := -T ${E_LDF} -L${E_LIBS_1} -L${E_LIBS_2} --strip-debug 

TGT_LDLIBS  := -le-lib 

TGT_POSTMAKE := echo "Finished building "$(TARGET)

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

# -Wall -std=c11 -nostdlib -nostartfiles
SRC_CFLAGS := ${OPTSZ_FLAG} ${DBG_FLAG} -Wall -std=gnu11 -nostdlib -nostartfiles -fno-default-inline 

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables 
CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics 
SRC_CXXFLAGS := ${OPTSZ_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2}

SRC_INCDIRS := $(SRC_ECORE_DIR) 

SOURCES := \
	$(SRC_ECORE_DIR)/e_start.s \
	$(SRC_ECORE_DIR)/interruptions.c \
	$(SRC_ECORE_DIR)/global.c \
	$(SRC_ECORE_DIR)/test1.cpp \
	$(SRC_ECORE_DIR)/trace.c \
	$(SRC_ECORE_DIR)/e_$(NAME_PRG).c 


