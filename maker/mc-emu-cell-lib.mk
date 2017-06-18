

TARGET := libmcm-cell.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SUBMAKEFILES := mc-emu-host.mk mc-emu-cell-kernel.mk

