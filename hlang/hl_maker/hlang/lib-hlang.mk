
TARGET := ${HLANG_LIB_DIR}/libhlang.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := ${HLANG_BMETAL_CFLAGS} ${HLANG_DBG_FLAG} 
SRC_CXXFLAGS := ${HLANG_BMETAL_CXXFLAGS} ${HLANG_DBG_FLAG} 

SRC_INCDIRS := ${HLANG_LIB_INCLUDES}

SOURCES := \
	${HLANG_BASE_DIR}/hlang.cpp \




