LIBS = _arduino.a
CEUFILE = tst.ceu
include ../one.mk

tst:
	make clean
	make CEUFILE=tst.ceu FLASHADDR=0x9000 all
	cd ../ && make clean && make APP=isr/tst.c
