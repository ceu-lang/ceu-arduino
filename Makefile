include Makefile.dirs

CEU_SRC ?= samples/blink-01.ceu
CEU_ISR ?= false

INO_SRC ?= env/env.ino

ARD_EXE = arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM*

PRESERVE = --preserve-temp-files

ARD_ARCH_UPPER  = $(shell echo $(ARD_ARCH) | tr a-z A-Z)
#ARD_ARCH_UPPER = $(call uc,$(ARD_ARCH))
ARD_BOARD_UPPER = $(shell echo $(ARD_BOARD) | tr a-z A-Z)

ifeq ($(CEU_ISR), true)
	CEU_ISR_INCS = -I./include/arduino/isr/$(ARD_ARCH)/ -I./include/arduino/isr/
	CEU_ISR_DEFS = -DCEU_FEATURES_ISR=1 #-DCEU_FEATURES_ISR_SLEEP=1
endif

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE) $(ARD_PREFS)                              \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)                        \
	           --port $(ARD_PORT)                                              \
	           --upload $(INO_SRC)

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include/ -I./include/ $(CEU_ISR_INCS) $(CEU_ISR_DEFS) -DCEUMAKER_ARDUINO -DARDUINO_ARCH_$(ARD_ARCH_UPPER)=1 -DARDUINO_BOARD_$(ARD_BOARD_UPPER)=1" \
	          --pre-input=$(CEU_SRC)                                           \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass               \
	          --ceu-line-directives=true                                       \
	          --ceu-features-lua=false --ceu-features-thread=false             \
	          --ceu-features-isr=$(CEU_ISR)                                    \
	    --env --env-types=env/types.h                                          \
	          --env-output=env/_ceu_app.c.h

.PHONY: all ceu
