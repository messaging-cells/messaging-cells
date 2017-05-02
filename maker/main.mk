
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


TARGET_DIR := ../bin

NUM_PRG=18
NAME_PRG=prog_$(NUM_PRG)

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
	bj-emu-dlmalloc-lib.mk \
	bj-znq-dlmalloc-lib.mk \
	bj-znq.mk \
	bj-emu-actor-lib.mk \
	bj-eph-actor-lib.mk \
	${EPH_SAMPLES_DIR}/logs_test.mk \
	${EMU_SAMPLES_DIR}/send_msg_emu.mk \
	${EPH_SAMPLES_DIR}/loader_bug.mk \
	${EPH_SAMPLES_DIR}/hello_world.mk \
	${EPH_SAMPLES_DIR}/send_msg.mk \
	${SRC_DIR}/test/modules/modules.mk \


# SUBMAKEFILES := bj-zynq.mk bj-ecore.mk 
# SUBMAKEFILES := bj-emu.mk 

default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
