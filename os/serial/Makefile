include ../one.mk

tst:
	make clean
	make CEUFILE=serial.ceu FLASHADDR=0x3000 all
	make CEUFILE=tst.ceu    FLASHADDR=0xD000 all
	cd ../ && make clean && make APP=serial/tst.c
