ifneq ($(MAKECMDGOALS),clean)
ifndef CEU
$(error USAGE: make CEU=<path-to-ceu-file>)
endif
endif

INO ?= *.ino

#This feature is available since beta release 1.5.2

#ARDUINO ?= arduino
ARDUINO = /opt/arduino-1.5.8/arduino
#ARDUINO = /opt/arduino-1.6.6/arduino
#ARDUINO = /opt/arduino-1.6.8/arduino

BOARD ?= nano
#BOARD = atmega328
#BOARD = lilypad328
#ARDUINOSUB = Microduino
#BOARD = 644pa16m

PORT ?= /dev/ttyACM0

.PHONY: all ceu ino clean

all: ceu
	$(ARDUINO) --verbose --board arduino:avr:$(BOARD):cpu=atmega168 --port $(PORT) --upload $(INO)

ceu:
	ceu $(CEU) --out-c _ceu_app.c.h

clean:
	rm -Rf /tmp/build*
	find . -name "_ceu_*" | xargs rm -f

### SIM ###
sim: sim-ceu ino _all
sim-ceu:
	ceu --timemachine --cpp-args "-I . -DCEUFILE=$(CEUFILE)" sim.ceu --out-c _ceu_app.src
sim-tst: sim-tst-ceu ino _all
sim-tst-ceu:
	ceu --timemachine --cpp-args "-I ." sim-tst.ceu --out-c _ceu_app.src
###

#CPPFLAGS += -Wno-pointer-arith -Wno-unused-label
#LINKFLAGS += -Wl,--section-start=.bootloader=0xE000
