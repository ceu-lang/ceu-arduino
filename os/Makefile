INOFILE ?= os.pde

#ARDUINOSUB = arduino
BOARD = uno
#BOARD = lilypad328
ARDUINOSUB = arduino
#BOARD = 644pa16m

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
