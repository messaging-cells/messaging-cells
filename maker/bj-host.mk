
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

# =======================================

TARGET := $(NAME_PRG)_elf

TGT_LDFLAGS := -L${H_LIB_1}

TGT_LDLIBS  := -le-hal -le-loader

TGT_POSTMAKE := echo "Finished building "$(TARGET)

TGT_CC := $(HCOMP)

TGT_LINKER := $(HCOMP)

# SRC_CFLAGS := -Wall -std=c11

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) $(H_INC_1) 

SOURCES := \
	$(SRC_HOST_DIR)/$(NAME_PRG).c \
	$(SRC_HOST_DIR)/prt_call_stack.c

