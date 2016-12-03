CEU_DIR  = $(error set absolute path to "<ceu>" repository)
CEU_SRC ?= samples/blink-01.ceu
CEU_ISR ?= false

ARD_EXE = arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM0

PRESERVE = --preserve-temp-files

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE)                                \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU)   \
	           --upload env/env.ino

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include -I./include"         \
	          --pre-input=$(CEU_SRC)                                \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass    \
	          --ceu-features-lua=false --ceu-features-thread=false  \
	          --ceu-features-isr=$(CEU_ISR)                         \
	    --env --env-types=env/types.h                               \
	          --env-output=env/_ceu_app.c.h

.PHONY: all ceu
