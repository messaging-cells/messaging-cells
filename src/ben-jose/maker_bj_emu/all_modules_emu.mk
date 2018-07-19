

# =======================================

SRC_CFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CFLAGS} ${MC_DBG_FLAG} 
SRC_CXXFLAGS := -DMC_IS_EMU_CODE ${MC_STD_EPH_CXXFLAGS} ${MC_DBG_FLAG} 

SRC_INCDIRS := ${BJ_HOST_INCLUDES}


SOURCES := \
	../dbg_only/dbg_only.cpp \
	../host_code/cnf_preload/preload_cnf.cpp \
	../host_code/cnf_preload/preload_sornet.cpp \
	../nervenet/nervenet.cpp \
	../sornet/sornet.cpp \
	../load_cnf/load_cnf.cpp \
	../load_cnf/load_sornet.cpp \
	../propag/propag.cpp \
	../stabi/mirrow.cpp \
	../stabi/stabi.cpp \
	../solver_main/solver.cpp \




