INOFILE ?= ../os.ino
INCLUDES += -I ../

ARDUINODIR = /usr/share/arduino
BOARD = uno
#lilypad328
#uno

.PHONY: all ino clean

all: apps _all

apps:
	cd ../serial/ && make target
	cd ../gpio/   && make target
	avr-objcopy ../serial/_ceu_app.o    --redefine-sym app=serial_app
	avr-objcopy ../serial/_ceu_serial.o --redefine-sym drv=serial_drv
	avr-objcopy ../gpio/_ceu_app.o      --redefine-sym app=gpio_app
	avr-objcopy ../gpio/_ceu_gpio.o     --redefine-sym drv=gpio_drv

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))
OBJECTS  += ../serial/_ceu_app.o ../serial/_ceu_serial.o ../serial/serial.o \
			../gpio/_ceu_app.o   ../gpio/_ceu_gpio.o

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
