
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

# -fno-extern-tls-init

TARGET_DIR := ./bin

MC_DBG_FLAG := -DFULL_DEBUG

MC_LIB_DIR := ../../bin

MC_LDF=mc-linker-script.ldf

MC_ESDK=${EPIPHANY_HOME}
MC_ETOOLS=${MC_ESDK}/tools

MC_STD_EPH_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

CXXFLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
CXXFLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
MC_STD_EPH_CXXFLAGS := ${CXXFLAGS_1} ${CXXFLAGS_2}

MC_EPH_LDFLAGS_1 := -L${MC_ETOOLS}/e-gnu/epiphany-elf/lib -L${MC_ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
MC_EPH_LDFLAGS_2 := -L${MC_LIB_DIR} -L${TARGET_DIR} ${MC_EPH_LDFLAGS_1} --strip-debug -static 
MC_STD_EPH_LDFLAGS := -T ${MC_LDF} ${MC_EPH_LDFLAGS_2}

MC_STD_EMU_LDFLAGS := -L${MC_LIB_DIR} -L${TARGET_DIR} 

MC_ZNQ_LDFLAGS_1 := -L${MC_ETOOLS}/host/lib 
MC_STD_ZNQ_LDFLAGS := -L${MC_LIB_DIR} -L${TARGET_DIR} ${MC_ZNQ_LDFLAGS_1} 

MC_STD_C_LDLIBS := -lc -lepiphany -lgcc -lg 
MC_STD_ZNQ_LDLIBS := -lmcz-cell -lmcz-tak-mak -lmcz-dlmalloc -le-hal -lm 
MC_STD_EMU_LDLIBS := -lmcm-cell -lmcm-tak-mak -lmcm-dlmalloc -lpthread
MC_STD_EPH_LDLIBS := -lmck-cell -lmck-tak-mak 

MC_CURR_DIR := $(shell pwd)

# MC_LIB_DIR_2 := ${MC_CURR_DIR}/../../bin
MC_LIB_DIR_2 := ../../../bin

MC_ZNQ_LIBS := ${MC_LIB_DIR_2}/libmcz-cell.a ${MC_LIB_DIR_2}/libmcz-tak-mak.a ${MC_LIB_DIR_2}/libmcz-dlmalloc.a
MC_EMU_LIBS := ${MC_LIB_DIR_2}/libmcm-cell.a ${MC_LIB_DIR_2}/libmcm-tak-mak.a ${MC_LIB_DIR_2}/libmcm-dlmalloc.a
MC_EPH_LIBS := ${MC_LIB_DIR_2}/libmck-cell.a ${MC_LIB_DIR_2}/libmck-tak-mak.a

MC_STD_INCDIRS := ../../cells ../../host ${MC_ETOOLS}/host/include

SUBMAKEFILES := \
	./host_code/no_nil_host.mk \
	./host_code/host_code.mk \
	./load_cnf/load_cnf.mk \


default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
