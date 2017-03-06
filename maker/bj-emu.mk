

TARGET := bj-emu-actor.elf

TGT_POSTMAKE := echo "Finished building "$(TARGET)

TGT_LDFLAGS := -pthread

SUBMAKEFILES := bj-emu-host.mk bj-emu-core.mk

