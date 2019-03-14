
BUILD_DIR := ./hl_tmp_build
TARGET_DIR := ./hl_install

HL_CURR_DIR := $(shell pwd)

SUBMAKEFILES := \
	./hlang/hlang.mk \


default: all
	@echo "Finished building hlang"

install: 
	@echo "Copy the files in ../bin to the desired install directories."

help: 
	@echo "See documentation in <base_dir>/docs."
