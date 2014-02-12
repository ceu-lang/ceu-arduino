INOFILE ?= ../os.ino
INCLUDES += -I ../ -I ../gpio/

ifndef TST
$(error missing test file)
endif

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all target ceu ino clean

all: ceu other _all
target: ceu other _target

other:
	cd ../gpio/   && make target
	cd ../serial/ && make target
	avr-objcopy ../gpio/_ceu_gpio.o     --redefine-sym drv=gpio
	avr-objcopy ../serial/_ceu_serial.o --redefine-sym drv=serial

ceu:
	ceu app1.ceu   	--os --verbose \
					--out-c _ceu_app1.c \
					--out-h _ceu_app1.h \
					--out-v app1 \
					--cpp-args "$(INCLUDES)"
	ceu app2.ceu   	--os --verbose \
					--out-c _ceu_app2.c \
					--out-h _ceu_app2.h \
					--out-v app2 \
					--cpp-args "$(INCLUDES)"
	ceu shell.ceu  	--os --verbose \
					--out-c _ceu_shell.c \
					--out-h _ceu_shell.h \
					--out-v shell \
					--cpp-args "$(INCLUDES)"
	ceu $(TST).ceu 	--os --verbose \
					--out-c _ceu_tst.c \
					--out-h _ceu_tst.h \
					--out-v tst \
					--cpp-args "$(INCLUDES)"

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))
OBJECTS  += ../serial/_ceu_serial.o ../serial/serial.o \
			../gpio/_ceu_gpio.o

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
