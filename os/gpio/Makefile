INOFILE ?= ../os.ino
INCLUDES += -I ../

ARDUINODIR = /usr/share/arduino
BOARD = uno
#lilypad328
#uno

.PHONY: all ceu ino clean

all: ceu _all

ceu:
	ceu app.ceu    	--os --verbose \
					--out-c _ceu_app.c \
					--out-h _ceu_app.h \
					--out-v app \
					--cpp-args "$(INCLUDES)"
	ceu gpio.ceu 	--os --verbose \
					--out-c _ceu_gpio.c \
					--out-h _ceu_gpio.h \
					--out-v drv \
					--cpp-args "$(INCLUDES)"

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
