
BJ_LDF := bj-lk-script.ldf

TARGET := ben-jose.elf

TGT_LDFLAGS := -T ${BJ_LDF} ${MC_EPH_LDFLAGS_2} --no-check-sections -L${TARGET_DIR}
TGT_LDLIBS  := -lload_cnf -lnervenet -lstabi ${MC_STD_EPH_LDLIBS}

TGT_PREREQS := \
	${MC_EPH_LIBS} \
	libnervenet.a \
	libload_cnf.a \
	libstabi.a \



#	${TARGET_DIR}/libload_cnf.a \

#	ln -s ../../../tests-ben-jose/cnfs/ .

#	e-objdump -h $(TARGET) > $(TARGET)_sizes.txt
#	e-objdump -D $(TARGET) > $(TARGET).s
#	cd $(MC_CURR_DIR)

#	e-objdump -h $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET)_sizes.txt
#	e-objdump -D $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET).s

define POST_OPERS
	rm $(TARGET_DIR)/cnfs
	ln -s ../../../tests-ben-jose/cnfs/ $(TARGET_DIR)
	e-objdump -h $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET)_sizes.txt
	e-objdump -D $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET).s
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld

SRC_CFLAGS := -DMC_IS_EPH_CODE ${MC_STD_EPH_CFLAGS} ${MC_DBG_FLAG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DMC_IS_EPH_CODE ${MC_STD_EPH_CXXFLAGS} ${MC_DBG_FLAG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${BJ_CORES_INCLUDES} 

SOURCES := solver.cpp


