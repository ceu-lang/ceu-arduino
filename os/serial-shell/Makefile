INOFILE ?= ../os.ino
INCLUDES += -I ../ -I ../gpio/

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all target other ino clean

all: ceu other _all
target: ceu other _target

other:
	cd ../serial/ && make target
	cd ../shell/  && make target

ceu:
	ceu serial_shell.ceu 	--os --verbose \
				--out-c _ceu_s2s.c \
				--out-h _ceu_s2s.h \
				--out-s S2S_SIZE \
				--out-f s2s_init \
				--cpp-args "$(INCLUDES)"

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

SOURCES  += $(wildcard $(addprefix ../, *.c *.cc *.cpp))
OBJECTS  += ../serial/_ceu_serial.o ../serial/serial.o \
	    ../shell/_ceu_shell.o

include ../../arduino.mk

CPPFLAGS += -Wno-pointer-arith
CPPFLAGS += -DCEU_OS
CPPFLAGS += $(INCLUDES)
