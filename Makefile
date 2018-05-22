include Makefile.dirs

CEU_SRC ?= samples/blink-01.ceu
CEU_ISR ?= false

INO_SRC ?= env/env.ino

ARD_EXE   = arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM*

# make ARD_BOARD=mega ARD_CPU=atmega2560    ARD_PORT=/dev/ttyACM1 CEU_ISR=true CEU_SRC=...
# make ARD_BOARD=pro  ARD_CPU=8MHzatmega328 ARD_PORT=/dev/ttyUSB0 CEU_ISR=true CEU_SRC=...

PRESERVE = --preserve-temp-files

ARD_ARCH_UPPER  = $(shell echo $(ARD_ARCH)  | tr a-z A-Z)
ARD_BOARD_UPPER = $(shell echo $(ARD_BOARD) | tr a-z A-Z)

ifeq ($(CEU_ISR), true)
	CEU_ISR_INCS = -I./include/arduino/isr/$(ARD_ARCH)/ -I./include/arduino/isr/
	CEU_ISR_DEFS = -DCEU_FEATURES_ISR=static -DCEU_FEATURES_ISR_STATIC -DCEU_FEATURES_ISR_SLEEP
	CEU_FEATURES = --ceu-features-isr=static
else
	CEU_FEATURES = --ceu-features-async=true
endif

ifdef ARD_CPU
	ARD_CPU_ = :cpu=$(ARD_CPU)
endif

ARD_PREFS = --pref compiler.cpp.extra_flags="$(CEU_ISR_DEFS)"

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE) $(ARD_PREFS)                              \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU_)             \
	           --port $(ARD_PORT)                                              \
	           --upload $(INO_SRC)

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include/ -I./include/ $(CEU_ISR_INCS) $(CEU_ISR_DEFS) -DCEUMAKER_ARDUINO -DARDUINO_ARCH_$(ARD_ARCH_UPPER) -DARDUINO_BOARD_$(ARD_BOARD_UPPER)" \
	          --pre-input=$(CEU_SRC)                                           \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass               \
	          --ceu-line-directives=true                                       \
	          --ceu-features-lua=false --ceu-features-thread=false             \
	          --ceu-features-callbacks=static $(CEU_FEATURES)                  \
	    --env --env-types=env/types.h                                          \
	          --env-output=env/_ceu_app.c.h

.PHONY: all ceu
