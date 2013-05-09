INOFILE ?= poll.ino
CEUFILE ?= samples/blink1.ceu

ARDUINODIR = /opt/arduino-1.0
BOARD = uno
#lilypad328
#uno

CEUCFILE = _ceu_$(notdir $(CEUFILE)).cceu

.PHONY: all ceu ino clean

all: ceu ino _all

ceu:
	ceu $(CEUFILE) --m4 --tp-word 2 --tp-pointer 2

ino:
	touch poll.ino async.ino

clean: _clean
	rm -f _ceu_* *.ceu_m4 samples/*.ceu_m4 *.hex *.o

include arduino.mk

CPPFLAGS += -Wno-pointer-arith
