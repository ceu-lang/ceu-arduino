LIBS = _arduino.a
include ../one.mk

tst:
	cd ../gpio/ && make clean && make CEUFILE=gpio.ceu FLASHADDR=0x2000 all
	make clean
	make CEUFILE=adc.ceu  FLASHADDR=0x7000 all
	make CEUFILE=tst.ceu  FLASHADDR=0x8000 all
	cd ../ && make clean && make APP=adc/tst.c
