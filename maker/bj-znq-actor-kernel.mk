
# =======================================

SRC_CFLAGS := -DIS_ZNQ_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} 
SRC_CXXFLAGS := -DIS_ZNQ_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} 

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ECORE_DIR) 

SOURCES := \
	$(SRC_ECORE_DIR)/log_znq.c \
	$(SRC_ECORE_DIR)/global.c \
	$(SRC_ECORE_DIR)/global_znq.cpp \
	$(SRC_ECORE_DIR)/binder.cpp \
	$(SRC_ECORE_DIR)/actor.cpp \
	$(SRC_ECORE_DIR)/actor_znq.cpp 

