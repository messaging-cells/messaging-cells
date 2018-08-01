
DBG_FLAG := -DFULL_DEBUG

#SRC_IN_SECTIONS := -fdata-sections -ffunction-sections
SRC_IN_SECTIONS := 

define SET_CROSS_COMPILE
ifeq "${CROSS_COMPILE+xxx}" ""
	ifeq "$(findstring arm,$(shell uname -p))" "arm"
		CROSS_COMPILE=
	else
		CROSS_COMPILE=arm-linux-gnueabihf-
	endif	
endif	
endef

$(eval $(SET_CROSS_COMPILE))

define SET_g_FLAG
ifeq "${DBG_FLAG}" ""
	g_FLAG := 
else
	g_FLAG := -g3
endif
endef

$(eval $(SET_g_FLAG))

MC_MAKER_DIR := $(shell pwd)

SRC_DIR := ${MC_MAKER_DIR}/../src

BUILD_DIR := ${MC_MAKER_DIR}/../tmp-build/lib-cells
TARGET_DIR := ${MC_MAKER_DIR}/../bin/lib-cells

ESDK=${EPIPHANY_HOME}
ETOOLS=${ESDK}/tools

STD_EPH_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

CXXFLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables 
CXXFLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
STD_EPH_CXXFLAGS := ${CXXFLAGS_1} ${CXXFLAGS_2}

SUBMAKEFILES := \
	pthreads/mc-ptd-tak-mak-lib.mk \
	pthreads/mc-ptd-dlmalloc-lib.mk \
	pthreads/mc-ptd-cell-lib.mk \
	parallella/manageru/mc-znq-tak-mak-lib.mk \
	parallella/manageru/mc-znq-dlmalloc-lib.mk \
	parallella/manageru/mc-znq-cell-lib.mk \
	parallella/workerus/mc-eph-tak-mak-lib.mk \
	parallella/workerus/mc-eph-cell-lib.mk \



default: all
	@echo "FINISHED_BUILDING_MESSAGING_CELLS"
	
parallella: ${TARGET_DIR}/libmck-cell.a \
	${TARGET_DIR}/libmck-tak-mak.a \
	${TARGET_DIR}/libmcz-tak-mak.a \
	${TARGET_DIR}/libmcz-dlmalloc.a \
	${TARGET_DIR}/libmcz-cell.a 
	@echo "FINISHED_BUILDING_PARALLELLA_MESSAGING_CELLS"

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
