INOFILE ?= poll.ino
CEUFILE ?= samples/blink1.ceu

ARDUINODIR = /usr/share/arduino
BOARD = uno
#lilypad328
#uno

CEUCFILE = _ceu_$(notdir $(CEUFILE)).cceu

.PHONY: all ceu ino clean

all: ceu ino _all

ceu:
	ceu $(CEUFILE)

ino:
	touch poll.ino async.ino

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

include arduino.mk

CPPFLAGS += -Wno-pointer-arith
