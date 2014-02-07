INOFILE ?= ../os.ino
INCLUDES += -I ../

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all ino clean

all: apps _all

apps:
	cd ../serial/ && make target
	cd ../gpio/   && make target
	avr-objcopy ../serial/_ceu_tst.o    --redefine-sym tst=serial_tst
	avr-objcopy ../serial/_ceu_serial.o --redefine-sym drv=serial_drv
	avr-objcopy ../gpio/_ceu_tst.o      --redefine-sym tst=gpio_tst
	avr-objcopy ../gpio/_ceu_gpio.o     --redefine-sym drv=gpio_drv

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))
OBJECTS  += ../serial/_ceu_tst.o ../serial/_ceu_serial.o ../serial/serial.o \
			../gpio/_ceu_tst.o   ../gpio/_ceu_gpio.o

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
