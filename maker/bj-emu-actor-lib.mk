

TARGET := libbjm-actor.a

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SUBMAKEFILES := bj-emu-host.mk bj-emu-actor-kernel.mk

