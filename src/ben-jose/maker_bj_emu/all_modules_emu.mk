

# =======================================

SRC_CFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CFLAGS} ${MC_DBG_FLAG} 
SRC_CXXFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CXXFLAGS} ${MC_DBG_FLAG} 

SRC_INCDIRS := ${BJ_HOST_INCLUDES}


SOURCES := \
	../host_code/cnf_preload/preload_cnf.cpp \
	../nervenet/nervenet.cpp \
	../load_cnf/load_cnf.cpp \
	../stabi/stabi.cpp \
	../solver_main/solver.cpp \




