

TARGET := libmcm-cell.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_PTHREADS_MANAGER := $(SRC_DIR)/pthreads/manageru

SUBMAKEFILES := \
	manageru/mc-ptd-manageru.mk \
	workerus/mc-ptd-cell-kernel.mk \

