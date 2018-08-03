
CNFS_DIR := ../../../tests-ben-jose/cnfs
CNFS_DIR := $(call CANONICAL_PATH,${CNFS_DIR})

MC_LIB_DIR := ../../bin/lib-cells

BUILD_DIR := ../../tmp-build/ben-jose
TARGET_DIR := ../../bin/ben-jose

MC_DBG_FLAG := -DFULL_DEBUG

MC_STD_EPH_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

CXXFLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
CXXFLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
MC_STD_EPH_CXXFLAGS := ${CXXFLAGS_1} ${CXXFLAGS_2}

MC_CURR_DIR := $(shell pwd)

SRC_BJ_DIR := ${MC_CURR_DIR}/..

MC_STD_INCDIRS := ${SRC_BJ_DIR}/../bin/lib-cells/mc_include ${MC_ETOOLS}/host/include
SRC_BJ_MANAGERU_DIR := ${SRC_BJ_DIR}/bj_manageru
SRC_BJ_WORKERU_DIR := ${SRC_BJ_DIR}/bj_workeru


BJ_WORKERUS_INCLUDES := \
	${MC_STD_INCDIRS} \
	${SRC_BJ_WORKERU_DIR} \


BJ_MANAGERU_INCLUDES := \
	${BJ_WORKERUS_INCLUDES} \
	${SRC_BJ_MANAGERU_DIR}/cnf_preload \
	${SRC_BJ_MANAGERU_DIR}/dimacs \
	${SRC_BJ_MANAGERU_DIR}/utils 

SUBMAKEFILES := \
	./bj_parallella/bj_parallella.mk \
	./bj_pthreads/bj_pthreads.mk \


default: all
	@echo "Finished building Lev-Ben-Jose"

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
