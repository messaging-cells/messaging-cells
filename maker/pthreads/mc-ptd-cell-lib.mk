

TARGET := libmcm-cell.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_PTHREADS_MANAGER := $(SRC_DIR)/pthreads/mc_manager

SUBMAKEFILES := \
	mc_manager/mc-ptd-host.mk \
	mc_workers/mc-ptd-cell-kernel.mk \

