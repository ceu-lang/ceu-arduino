INOFILE ?= poll.ino
CEUFILE ?= samples/blink1.ceu

ARDUINOSUB = Microduino
BOARD = 644pa16m
#ARDUINOSUB = arduino
#BOARD = uno
#lilypad328
#uno

.PHONY: all ceu ino clean

all: ceu ino _all

ceu:
	ceu $(CEUFILE) --out-c _ceu_app.src

ino:
	touch poll.ino async.ino

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

include arduino.mk

CPPFLAGS += -Wno-pointer-arith
#LINKFLAGS += -Wl,--section-start=.bootloader=0xE000
