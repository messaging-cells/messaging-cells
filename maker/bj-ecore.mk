
IS_CORE_FLAG := -DIS_CORE_CODE

# DIR_ELIBS_1=${ETOOLS}/e-gnu/epiphany-elf/lib
DIR_ELIBS_1 := 
# DIR_ELIBS_2=${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
DIR_ELIBS_2 := 

E_LDF=bj-ld-script.ldf
# ELDF=${ESDK}/bsps/current/fast.ldf

SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 

# OPTSZ_FLAG := -Os # DOES NOT WORK WITH e-gcc ???? BAD GENERATED CODE ????
OPTSZ_FLAG := 

# STDLIBS := -lc -lepiphany -lgcc -lg 
STDLIBS := 

# ELIBS := -le-lib 
ELIBS :=

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

#LD_IN_SECTIONS := --gc-sections
LD_IN_SECTIONS := 

# =======================================

TARGET := bj-core-actor.elf

LD_FLAGS_1 := -static
TGT_LDFLAGS := -T ${E_LDF} -L${DIR_ELIBS_1} -L${DIR_ELIBS_2} --strip-debug ${LD_IN_SECTIONS} ${LD_FLAGS_1}

TGT_LDLIBS  := ${STDLIBS} ${ELIBS}

TGT_POSTMAKE := echo "Finished building "$(TARGET)

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

# -Wall -std=c11 -nostdlib -nostartfiles
C_FLAGS_1 := -ffreestanding -Wall -std=gnu11 -nostdlib -nostartfiles -fno-default-inline ${SRC_IN_SECTIONS}
SRC_CFLAGS := ${IS_CORE_FLAG} ${OPTSZ_FLAG} ${DBG_FLAG} ${C_FLAGS_1}

# -std=c++11 -nostdlib -fno-exceptions -fno-unwind-tables -fno-rtti -Os
CXX_FLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables ${SRC_IN_SECTIONS}
CXX_FLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
SRC_CXXFLAGS := ${IS_CORE_FLAG} ${OPTSZ_FLAG} ${DBG_FLAG} ${CXX_FLAGS_1} ${CXX_FLAGS_2}

SRC_INCDIRS := $(SRC_ECORE_DIR) 

#	$(SRC_ECORE_DIR)/test_logs.c \
#	$(SRC_ECORE_DIR)/umm_malloc.c \
#	$(SRC_ECORE_DIR)/dyn_mem.cpp \
#	$(SRC_ECORE_DIR)/actor.cpp \
#	$(SRC_ECORE_DIR)/std2.c \

SOURCES := \
	$(SRC_ECORE_DIR)/interruptions.c \
	$(SRC_ECORE_DIR)/umm_malloc.c \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_ECORE_DIR)/global.c \
	$(SRC_ECORE_DIR)/rr_array.c \
	$(SRC_ECORE_DIR)/trace.c \
	$(SRC_ECORE_DIR)/core_main.c \
	$(SRC_ECORE_DIR)/test_logs.c \
	$(SRC_ECORE_DIR)/e_start.s \
	$(SRC_ECORE_DIR)/dyn_mem.cpp \
	$(SRC_ECORE_DIR)/binder.cpp \
	$(SRC_ECORE_DIR)/actor.cpp 


