
TARGET := modules/libmod_3.a

TGT_PREREQS := libcommon.a

define POST_OPERS
	modules/mod_make_redef_list.sh $(TARGET_DIR)/$(TARGET) m3
	modules/mod_repl_common_syms.sh $(TARGET_DIR)/$(TARGET) m3 module3_code module3_data
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

TGT_CC := e-gcc
TGT_CXX := e-g++

SRC_CFLAGS := -DIS_CORE_CODE ${BJ_STD_EPH_CFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DIS_CORE_CODE ${BJ_STD_EPH_CXXFLAGS} ${BJ_DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${BJ_STD_INCDIRS}

SOURCES := common.cpp pru_3.cpp


