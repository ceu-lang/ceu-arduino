INOFILE ?= poll.ino
CEUFILE ?= samples/blink1.ceu

ARDUINODIR = /usr/share/arduino
BOARD = uno
#lilypad328
#uno

.PHONY: all ceu ino clean all-os ceu-os os

all: ceu ino _all

all-os: os ceu-os ino _all

ceu:
	ceu $(CEUFILE)
ceu-os:
	ceu $(CEUFILE) --os --out-c util/_ceu_app.c --out-h util/_ceu_app.h

ino:
	touch poll.ino async.ino os.pde

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

include arduino.mk

CPPFLAGS += -Wno-pointer-arith
