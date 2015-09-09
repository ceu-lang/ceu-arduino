INOFILE ?= poll.ino
CEUFILE ?= samples/blink1.ceu

ARDUINOSUB = arduino
BOARD = uno
#BOARD = atmega328
#BOARD = lilypad328
#ARDUINOSUB = Microduino
#BOARD = 644pa16m

.PHONY: all ceu ino clean

all: ceu ino _all

ceu:
	ceu $(CEUFILE) --out-c _ceu_app.src

ino:
	touch poll.ino async.ino gd.ino

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

### SIM ###
sim: sim-ceu ino _all
sim-ceu:
	ceu --timemachine --cpp-args "-I . -DCEUFILE=$(CEUFILE)" sim.ceu --out-c _ceu_app.src
sim-tst: sim-tst-ceu ino _all
sim-tst-ceu:
	ceu --timemachine --cpp-args "-I ." sim-tst.ceu --out-c _ceu_app.src
###

include arduino.mk

CPPFLAGS += -Wno-pointer-arith -Wno-unused-label
#LINKFLAGS += -Wl,--section-start=.bootloader=0xE000
