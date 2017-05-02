

TARGET := libbjm-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

# TGT_LDFLAGS := -Ur -pthread -L${TARGET_DIR}
# TGT_LDLIBS  := -lbjm-dlmalloc -lbjm-tak-mak
# TGT_PREREQS := libbjm-dlmalloc.a libbjm-tak-mak.a

SUBMAKEFILES := bj-emu-host.mk bj-emu-core.mk

