
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


TARGET_DIR := ./bin

BJ_DBG_FLAG := -DFULL_DEBUG

BJ_LDF=bj-linker-script.ldf

BJ_ESDK=${EPIPHANY_HOME}
BJ_ETOOLS=${BJ_ESDK}/tools

BJ_STD_EPH_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

CXXFLAGS_1 := -Wall -std=c++14 -nostdlib -fno-exceptions -fno-unwind-tables 
CXXFLAGS_2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BJ_STD_EPH_CXXFLAGS := ${CXXFLAGS_1} ${CXXFLAGS_2}

BJ_EPH_LDFLAGS_1 := -L${BJ_ETOOLS}/e-gnu/epiphany-elf/lib -L${BJ_ETOOLS}/e-gnu/lib/gcc/epiphany-elf/5.4.0/
BJ_STD_EPH_LDFLAGS := -T ${BJ_LDF} -L../../bin -L${TARGET_DIR} ${BJ_EPH_LDFLAGS_1} --strip-debug -static 

BJ_STD_EMU_LDFLAGS := -L../../bin -L${TARGET_DIR} 

BJ_ZNQ_LDFLAGS_1 := -L${BJ_ETOOLS}/host/lib 
BJ_STD_ZNQ_LDFLAGS := -L../../bin -L${TARGET_DIR} ${BJ_ZNQ_LDFLAGS_1} 

BJ_STD_C_LDLIBS := -lc -lepiphany -lgcc -lg 
BJ_STD_ZNQ_LDLIBS := -lbjz-actor -lbjz-tak-mak -lbjz-dlmalloc -le-hal -lm 
BJ_STD_EMU_LDLIBS := -lbjm-actor -lbjm-tak-mak -lbjm-dlmalloc -lpthread
BJ_STD_EPH_LDLIBS := -lbjk-actor -lbjk-tak-mak 

BJ_STD_INCDIRS := ../../actors ../../host ${BJ_ETOOLS}/host/include

#	./tak_mak_test/test_tak_mak.mk \
#	./logs_test/logs_test.mk \
#	./eph_dev_driver_bug/eph_dev_driver_bug.mk \
#	./dlmalloc_test/test_dlmalloc_emu.mk \
#	./dlmalloc_test/test_dlmalloc_znq.mk \
#	./modules/modules.mk \
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

SUBMAKEFILES := \
	./nil_host/nil_host.mk \
	./hello_world/hello_world.mk \
	./send_msg/send_msg_eph.mk \
	./send_msg/send_msg_emu.mk \
	./eating_philo/philo_emu.mk \



default: all

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
