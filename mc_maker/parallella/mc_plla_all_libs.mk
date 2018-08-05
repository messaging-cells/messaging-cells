
define SET_CROSS_COMPILE
ifeq "${CROSS_COMPILE+xxx}" ""
	ifeq "$(findstring arm,$(shell uname -p))" "arm"
		CROSS_COMPILE=
	else
		CROSS_COMPILE=arm-linux-gnueabihf-
	endif	
endif	
endef

$(eval $(SET_CROSS_COMPILE))

ESDK=${EPIPHANY_HOME}
ETOOLS=${ESDK}/tools

MC_PLLA_LIB_DIR := parallella/lib/

SUBMAKEFILES := \
	manageru/mc-znq-tak-mak-lib.mk \
	manageru/mc-znq-dlmalloc-lib.mk \
	manageru/mc-znq-cell-lib.mk \
	workerus/mc-eph-tak-mak-lib.mk \
	workerus/mc-eph-cell-lib.mk \

parallella: ${TARGET_DIR}/libmck-cell.a \
	${TARGET_DIR}/libmck-tak-mak.a \
	${TARGET_DIR}/libmcz-tak-mak.a \
	${TARGET_DIR}/libmcz-dlmalloc.a \
	${TARGET_DIR}/libmcz-cell.a 
	@echo "FINISHED_BUILDING_PARALLELLA_MESSAGING_CELLS"

