
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

TARGET := libbjk-actor.a

LD_FLAGS_1 := -static
TGT_LDFLAGS := -T ${E_LDF} -Ur -L${DIR_ELIBS_1} -L${DIR_ELIBS_2} --strip-debug ${LD_IN_SECTIONS} ${LD_FLAGS_1}

TGT_LDLIBS  := ${STDLIBS} ${ELIBS}

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc

TGT_CXX := e-g++

TGT_LINKER := e-ld

SRC_CFLAGS := -DIS_CORE_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_ECORE_DIR) 

#	$(SRC_ECORE_DIR)/test_logs.c \
#	$(SRC_ECORE_DIR)/umm_malloc.c \
#	$(SRC_ECORE_DIR)/log.c \
#	$(SRC_ECORE_DIR)/dyn_mem.cpp \
#	$(SRC_ECORE_DIR)/actor.cpp \
#	$(SRC_ECORE_DIR)/std2.c \
#	$(SRC_ECORE_DIR)/a_shd_code_error.cpp \
#	$(SRC_ECORE_DIR)/call_bj_cores_main_eph.c \


SOURCES := \
	$(SRC_ECORE_DIR)/interruptions.c \
	$(SRC_ECORE_DIR)/umm_malloc.c \
	$(SRC_ECORE_DIR)/umm_malloc_eph.c \
	$(SRC_ECORE_DIR)/link_syms_struct_eph.c \
	$(SRC_ECORE_DIR)/log.c \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_ECORE_DIR)/shared_eph.c \
	$(SRC_ECORE_DIR)/global.c \
	$(SRC_ECORE_DIR)/global_eph.c \
	$(SRC_ECORE_DIR)/rr_array.c \
	$(SRC_ECORE_DIR)/trace_eph.c \
	$(SRC_ECORE_DIR)/e_start.s \
	$(SRC_ECORE_DIR)/dyn_mem.c \
	$(SRC_ECORE_DIR)/call_bj_cores_main_eph.c \
	$(SRC_ECORE_DIR)/binder.cpp \
	$(SRC_ECORE_DIR)/actor_eph.cpp \
	$(SRC_ECORE_DIR)/actor.cpp \


