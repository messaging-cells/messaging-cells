

TARGET := libmcm-cell.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_PTHREADS_MANAGER := $(SRC_DIR)/pthreads/manager

SUBMAKEFILES := \
	manager/mc-emu-host.mk \
	workers/mc-emu-cell-kernel.mk \

