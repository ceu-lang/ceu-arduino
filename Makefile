CEU_DIR = $(error set absolute path to "<ceu>" repository)

#ARD_EXE = arduino
ARD_EXE   = /opt/arduino-1.6.12/arduino
ARD_ARCH  = avr
ARD_BOARD = uno
ARD_PORT  = /dev/ttyACM0
#ARD_BOARD = mega
#ARD_BOARD = lilypad328
#ARD_BOARD = Microduino
#ARD_BOARD = 644pa16m
#ARD_CPU = :cpu=atmega328p
#ARD_CPU = :cpu=atmega168

PRESERVE = --preserve-temp-files

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE)								\
			   --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU)	\
			   --upload env/env.ino

_c:
	$(ARD_EXE) --verbose $(PRESERVE)								\
			   --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU)	\
			   --port $(ARD_PORT) --upload env/env.ino

ceu:
	ceu --pre --pre-args="-I$(CEU_DIR)/include -I./include"         \
	          --pre-input=samples/blink-01.ceu                      \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass    \
			  --ceu-features-lua=false --ceu-features-thread=false  \
	          --ceu-features-isr=true \
	    --env --env-types=env/types.h								\
	          --env-output=env/_ceu_app.c.h

.PHONY: all ceu
