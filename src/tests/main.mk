
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

#	./tak_mak_test/test_tak_mak.mk \
#	./logs_test/logs_test.mk \
#	./eph_dev_driver_bug/eph_dev_driver_bug.mk \
#	./dlmalloc_test/test_dlmalloc_emu.mk \
#	./dlmalloc_test/test_dlmalloc_znq.mk \
#	./test_addr_conv/addr_conv.mk \
#	./znq_tests/znq_hello.mk \
#	./znq_tests/znq_backtrace.mk \
#	./backtrace/backtrace.mk \
#	./min_host/min_host.mk \
#	./min_host/min_host_emu.mk \
#	./hello_class/hello_class.mk \
#	./sequence/sequence.mk \
#	./sequence/sequence_2.mk \
#	./sequence/sequence_3.mk \
#	./send_host_msg/send_host_msg_emu.mk \
#	./send_msg/send_msg_eph.mk \
#	./send_msg/send_msg_emu.mk \
#	./send_host_msg/send_host_msg_emu.mk \
#	./send_host_msg/send_host_msg_eph.mk \
#	./send_host_msg/send_host_msg_znq.mk \
#	./emu_tests/hola_jose.mk \
#	./modules/modules.mk \

SUBMAKEFILES := \
	./nil_host/no_nil_host.mk \
	./nil_host/nil_host.mk \
	./hello_world/hello_world.mk \
	./eating_philo/philo_emu.mk \
	./eating_philo/philo_eph.mk \
	./send_host_msg/send_host_msg_emu.mk \
	./send_host_msg/send_host_msg_eph.mk \
	./send_host_msg/send_host_msg_znq.mk \
	./send_msg/send_msg_eph.mk \
	./modules/modules.mk \



default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
