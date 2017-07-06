
# =======================================

SRC_CFLAGS := -DMC_IS_ZNQ_CODE ${MC_STD_EPH_CFLAGS} ${DBG_FLAG} 
SRC_CXXFLAGS := -DMC_IS_ZNQ_CODE ${MC_STD_EPH_CXXFLAGS} ${DBG_FLAG} 

SRC_INCDIRS := \
	$(MC_STD_INCDIRS) \
	$(SRC_BJ_HOST_DIR)/cnf_preload \
	$(SRC_BJ_HOST_DIR)/dimacs \
	$(SRC_BJ_HOST_DIR)/utils 

SOURCES := \
	cnf_preload/preload_cnf.cpp \


