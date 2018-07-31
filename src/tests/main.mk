

#*************************************************************
#
#This file is part of messaging-cells.
#
#messaging-cells is free software: you can redistribute it and/or modify
#it under the terms of the version 3 of the GNU General Public 
#License as published by the Free Software Foundation.
#
#messaging-cells is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with messaging-cells.  If not, see <http://www.gnu.org/licenses/>.
#
#------------------------------------------------------------
#
#Copyright (C) 2017-2018. QUIROGA BELTRAN, Jose Luis.
#Id (cedula): 79523732 de Bogota - Colombia.
#See https://messaging-cells.github.io/
#
#messaging-cells is free software thanks to The Glory of Our Lord 
#	Yashua Melej Hamashiaj.
#Our Resurrected and Living, both in Body and Spirit, 
#	Prince of Peace.
#
#------------------------------------------------------------


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

BUILD_DIR := ../../tmp-build/tests
TARGET_DIR := ../../bin/tests

MC_DBG_FLAG := -DFULL_DEBUG

MC_LIB_DIR := ../../bin/lib-cells

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
# MC_STD_ZNQ_LDLIBS := -lmcz-cell -lmcz-tak-mak -lmcz-dlmalloc -le-hal -lm 
MC_STD_ZNQ_LDLIBS := -lmcz-cell -lmcz-tak-mak -lmcz-dlmalloc -le-hal -lm -static-libstdc++ -static-libgcc 
MC_STD_EMU_LDLIBS := -lmcm-cell -lmcm-tak-mak -lmcm-dlmalloc -lpthread
MC_STD_EPH_LDLIBS := -lmck-cell -lmck-tak-mak 

MC_CURR_DIR := $(shell pwd)

# MC_LIB_DIR_2 := ${MC_CURR_DIR}/../../bin
MC_LIB_DIR_2 := ../lib-cells

MC_ZNQ_LIBS := ${MC_LIB_DIR_2}/libmcz-cell.a ${MC_LIB_DIR_2}/libmcz-tak-mak.a ${MC_LIB_DIR_2}/libmcz-dlmalloc.a
MC_EMU_LIBS := ${MC_LIB_DIR_2}/libmcm-cell.a ${MC_LIB_DIR_2}/libmcm-tak-mak.a ${MC_LIB_DIR_2}/libmcm-dlmalloc.a
MC_EPH_LIBS := ${MC_LIB_DIR_2}/libmck-cell.a ${MC_LIB_DIR_2}/libmck-tak-mak.a

MC_STD_INCDIRS := ../../cells ../../cells/mc_manager ${MC_ETOOLS}/host/include

#	./tak_mak_test/test_tak_mak.mk \
#	./logs_test/logs_test.mk \
#	./eph_dev_driver_bug/eph_dev_driver_bug.mk \
#	./dlmalloc_test/test_dlmalloc_ptd.mk \
#	./dlmalloc_test/test_dlmalloc_znq.mk \
#	./test_addr_conv/addr_conv.mk \
#	./znq_tests/znq_hello.mk \
#	./znq_tests/znq_backtrace.mk \
#	./backtrace/backtrace.mk \
#	./min_host/min_host.mk \
#	./min_host/min_host_ptd.mk \
#	./hello_class/hello_class.mk \
#	./sequence/sequence.mk \
#	./sequence/sequence_2.mk \
#	./sequence/sequence_3.mk \
#	./send_host_msg/send_host_msg_ptd.mk \
#	./send_msg/send_msg_eph.mk \
#	./send_msg/send_msg_ptd.mk \
#	./send_host_msg/send_host_msg_ptd.mk \
#	./send_host_msg/send_host_msg_eph.mk \
#	./send_host_msg/send_host_msg_znq.mk \
#	./ptd_tests/hola_jose.mk \
#	./modules/modules.mk \

SUBMAKEFILES := \
	./nil_host/no_nil_host.mk \
	./nil_host/nil_host.mk \
	./logs_test/logs_test.mk \
	./hello_world/hello_world.mk \
	./send_msg/send_msg_eph.mk \
	./send_msg/send_msg_ptd.mk \
	./eating_philo/philo_ptd.mk \
	./eating_philo/philo_eph.mk \
	./send_host_msg/send_host_msg_ptd.mk \
	./send_host_msg/send_host_msg_eph.mk \
	./send_host_msg/send_host_msg_znq.mk \
	./modules/modules.mk \



default: all
	@echo "Finished building Messaging Cell TESTS"

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
