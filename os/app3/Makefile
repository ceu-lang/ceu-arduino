INOFILE ?= ../os.ino
INCLUDES += -I ../ -I ../gpio/

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all ino clean

all: ceu other _all

other:
	cd ../gpio/   && make target
	avr-objcopy ../gpio/_ceu_gpio.o --redefine-sym drv=gpio

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
	ceu app.ceu  	--os --verbose \
					--out-c _ceu_tst.c \
					--out-h _ceu_tst.h \
					--out-v app \
					--cpp-args "$(INCLUDES)"

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))
OBJECTS  += ../gpio/_ceu_gpio.o

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
