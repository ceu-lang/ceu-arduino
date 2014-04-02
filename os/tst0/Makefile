LIBS = _arduino.a
CEUFILE = tst.ceu
include ../one.mk

tst:
	make clean
	make CEUFILE=tst.ceu FLASHADDR=0x2000 all
	cd ../ && make clean && make APP=tst0/tst.c
