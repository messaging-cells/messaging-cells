
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
	g_FLAG := -g
endif
endef

$(eval $(SET_g_FLAG))


TARGET_DIR := ../bin

ESDK=${EPIPHANY_HOME}
ETOOLS=${ESDK}/tools

SRC_DIR := ../src

EPH_SAMPLES_DIR := ./eph_samples
EMU_SAMPLES_DIR := ./emu_samples

STD_EPH_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

CXXFLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables 
CXXFLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
STD_EPH_CXXFLAGS := ${CXXFLAGS_1} ${CXXFLAGS_2}

ATVA_EPH_LFLAGS := -L${ETOOLS}/e-gnu/epiphany-elf/lib -L${ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/

SUBMAKEFILES := \
	bj-emu-tak-mak-lib.mk \
	bj-eph-tak-mak-lib.mk \
	bj-znq-tak-mak-lib.mk \
	bj-emu-dlmalloc-lib.mk \
	bj-znq-dlmalloc-lib.mk \
	bj-znq-actor-lib.mk \
	bj-emu-actor-lib.mk \
	bj-eph-actor-lib.mk \



default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
