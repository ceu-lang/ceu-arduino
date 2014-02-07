INOFILE ?= ../os.ino
INCLUDES += -I ../

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all target ceu ino clean

all:    ceu _all
target: ceu _target

ceu:
	ceu tst.ceu    	--os --verbose \
					--out-c _ceu_tst.c \
					--out-h _ceu_tst.h \
					--out-v tst \
					--cpp-args "$(INCLUDES)"
	ceu serial.ceu 	--os --verbose \
					--out-c _ceu_serial.c \
					--out-h _ceu_serial.h \
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
