
SRC_ACTORS_DIR := $(SRC_DIR)/actors

# =======================================

TARGET := libbjk-tak-mak.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_CC := e-gcc
TGT_CXX := e-g++

SRC_CFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DBJ_IS_EPH_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := $(SRC_ACTORS_DIR) 

SOURCES := $(SRC_ACTORS_DIR)/tak_mak.cpp 

