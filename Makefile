include Makefile.dirs

CEU_SRC ?= samples/blink-01.ceu
CEU_ISR ?= false

INO_SRC ?= env/env.ino

ARD_EXE = arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM*

PRESERVE = --preserve-temp-files

ARD_ARCH_UPPER = $(shell echo $(ARD_ARCH) | tr a-z A-Z)
#ARD_ARCH_UPPER = $(call uc,$(ARD_ARCH))

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE)                                           \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)                        \
	           --port $(ARD_PORT)                                              \
	           --upload $(INO_SRC)

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include -I./include -DCEUMAKER_ARDUINO -DARDUINO_ARCH_$(ARD_ARCH_UPPER)" \
	          --pre-input=$(CEU_SRC)                                           \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass               \
	          --ceu-features-lua=false --ceu-features-thread=false             \
	          --ceu-features-isr=$(CEU_ISR)                                    \
	    --env --env-types=env/types.h                                          \
	          --env-output=env/_ceu_app.c.h

.PHONY: all ceu
