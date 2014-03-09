INOFILE ?= os.ino

ARDUINOSUB = Microduino
#BOARD = uno
BOARD = 644pa16m
#lilypad328
#uno

.PHONY: all target clean

all:    _all
	nm os.elf -S -n|grep CEU_APP_ADDR

target: _target

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

ifndef APP
#$(error missing MAIN application)
endif

SOURCES += $(APP)

include ../arduino.mk

CPPFLAGS += -Wno-pointer-arith -mrelax
CPPFLAGS += -DCEU_OS
