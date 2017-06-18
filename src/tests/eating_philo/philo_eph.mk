
PHILO_DBG := -DFULL_DEBUG

define SET_STD_LIB_LDFLAG
ifeq "${PHILO_DBG}" ""
	PHILO_STD_C_LDLIBS := 
else
	PHILO_STD_C_LDLIBS := ${MC_STD_C_LDLIBS}
endif	
endef

$(eval $(SET_STD_LIB_LDFLAG))


# =======================================

PHILO_LDF=eating_philo/philo.ldf

TARGET := philo_eph.elf

TGT_LDFLAGS := -T ${PHILO_LDF} ${MC_EPH_LDFLAGS_2} ${LD_IN_SECTIONS} 
TGT_LDLIBS  := ${MC_STD_EPH_LDLIBS} ${PHILO_STD_C_LDLIBS}
TGT_PREREQS := ${MC_EPH_LIBS}

TGT_CC := e-gcc
TGT_CXX := e-g++
TGT_LINKER := e-ld

define POST_OPERS
	e-objdump -D $(TARGET_DIR)/$(TARGET) > $(TARGET_DIR)/$(TARGET).s
	printf "====================================\nFinished building "$(TARGET)"\n\n\n" 
endef

TGT_POSTMAKE := ${POST_OPERS}

SRC_CFLAGS := -DMC_IS_EPH_CODE ${MC_STD_EPH_CFLAGS} ${PHILO_DBG} ${SRC_IN_SECTIONS}
SRC_CXXFLAGS := -DMC_IS_EPH_CODE ${MC_STD_EPH_CXXFLAGS} ${PHILO_DBG} ${SRC_IN_SECTIONS}

SRC_INCDIRS := ${MC_STD_INCDIRS}

SOURCES := philo.cpp


