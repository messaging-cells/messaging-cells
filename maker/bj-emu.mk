

# TARGET := bj-emu-actor.elf
TARGET := libbj-emu-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

TGT_LDFLAGS := -Ur -pthread -L${TARGET_DIR}
TGT_LDLIBS  := -ldlmallocemu
TGT_PREREQS := libdlmallocemu.a

SUBMAKEFILES := bj-emu-host.mk bj-emu-core.mk

