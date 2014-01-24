INOFILE ?= ../os.pde
CEUFILE ?= samples/blink1.ceu

ARDUINODIR = /usr/share/arduino
BOARD = uno
#lilypad328
#uno

.PHONY: all ceu ino clean

all: ceu ino _all

ceu:
	ceu led1.ceu --os --verbose \
					--out-c _ceu_led1.c \
					--out-h _ceu_led1.h \
					--out-v app_led1
	ceu gpio.ceu --os --verbose \
					--out-c _ceu_gpio.c \
					--out-h _ceu_gpio.h \
					--out-v drv_gpio

ino:
	touch os.pde

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

include ../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
