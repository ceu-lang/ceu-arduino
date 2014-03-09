LIBS = _arduino.a
include ../one.mk

tst:
	make clean
	make CEUFILE=gpio.ceu FLASHADDR=0x2000 all
	make CEUFILE=tst.ceu  FLASHADDR=0xE000 all
	cd ../ && make clean && make APP=gpio/tst.c
