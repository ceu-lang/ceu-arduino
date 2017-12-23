include Makefile.dirs

CEU_SRC ?= samples/blink-01.ceu
CEU_ISR ?= false

INO_SRC ?= env/env.ino

ARD_EXE = /opt/arduino/arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM*
#ARD_PREFS = --pref build.extra_flags="-fconserve-stack" #-O0 -Wall

PRESERVE = --preserve-temp-files

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE) $(ARD_PREFS)                              \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)                        \
	           --port $(ARD_PORT)                                              \
	           --upload $(INO_SRC)

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include -I./include -DCEUMAKER_ARDUINO" \
	          --pre-input=$(CEU_SRC)                                           \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass               \
	          --ceu-line-directives=false \
	          --ceu-callbacks-lines=false                                      \
	          --ceu-features-lua=false --ceu-features-thread=false             \
	          --ceu-features-isr=$(CEU_ISR)                                    \
	    --env --env-types=env/types.h                                          \
	          --env-output=env/_ceu_app.c.h

pre:
	ceu --pre --pre-args="-I$(CEU_DIR)/include -I./include -DCEUMAKER_ARDUINO" \
	          --pre-input=$(CEU_SRC) --pre-output=/tmp/x.ceu

.PHONY: all ceu
