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
	avr-objcopy ../serial/_ceu_tst.o --redefine-sym tst_init=serial_tst_init
	avr-objcopy ../serial/_ceu_tst.o --redefine-sym TST_SIZE==SERIAL_TST_SIZE
	avr-objcopy ../gpio/_ceu_tst.o   --redefine-sym tst_init=gpio_tst_init
	avr-objcopy ../gpio/_ceu_tst.o   --redefine-sym TST_SIZE=GPIO_TST_SIZE

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
