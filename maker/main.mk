
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

SUBMAKEFILES := dlmalloc-emu.mk dlmalloc-znq.mk bj-zynq.mk bj-ecore.mk bj-emu.mk bj-bug-ecore.mk
# SUBMAKEFILES := bj-zynq.mk bj-ecore.mk 
# SUBMAKEFILES := bj-emu.mk 

default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
