
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

HCOMP=$(CROSS_COMPILE)gcc

H_DIR=${ESDK}/tools/host

H_LIB_1=${ETOOLS}/host/lib
H_INC_1=${ETOOLS}/host/include

SRC_HOST_DIR := $(SRC_DIR)/host
SRC_ECORE_DIR := $(SRC_DIR)/ecore

DBG_FLAG := -DFULL_DEBUG
# DBG_FLAG := 


# =======================================

TARGET := bj-actor-booter.elf

TGT_LDFLAGS := -L${H_LIB_1}

TGT_LDLIBS  := -le-hal -le-loader

TGT_POSTMAKE := echo "Finished building "$(TARGET)

TGT_CC := $(HCOMP)

TGT_LINKER := $(HCOMP)

SRC_CFLAGS := -Wall -std=gnu11 ${DBG_FLAG} 
SRC_CXXFLAGS := -Wall -std=c++14 ${DBG_FLAG} 

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) $(H_INC_1) 

SOURCES := \
	$(SRC_HOST_DIR)/booter.c \
	$(SRC_HOST_DIR)/prt_call_stack.c \
	$(SRC_ECORE_DIR)/shared.c \
	$(SRC_ECORE_DIR)/rr_array.c 

