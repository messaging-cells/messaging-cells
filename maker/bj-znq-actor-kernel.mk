
# =======================================

SRC_CFLAGS := -DBJ_IS_ZNQ_CODE ${STD_EPH_CFLAGS} ${DBG_FLAG} 
SRC_CXXFLAGS := -DBJ_IS_ZNQ_CODE ${STD_EPH_CXXFLAGS} ${DBG_FLAG} 

SRC_INCDIRS := $(SRC_HOST_DIR) $(SRC_ACTORS_DIR) 

SOURCES := \
	$(SRC_ACTORS_DIR)/log_znq.c \
	$(SRC_ACTORS_DIR)/err_msgs.c \
	$(SRC_ACTORS_DIR)/global.c \
	$(SRC_ACTORS_DIR)/global_znq.cpp \
	$(SRC_ACTORS_DIR)/binder.cpp \
	$(SRC_ACTORS_DIR)/actor.cpp \
	$(SRC_ACTORS_DIR)/actor_znq.cpp 

