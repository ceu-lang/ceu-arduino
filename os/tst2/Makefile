include ../one.mk

tst:
	cd ../gpio && make clean && make CEUFILE=gpio.c FLASHADDR=0x2000 all
	make clean
	make CEUFILE=app1.ceu FLASHADDR=0x3000 all
	make CEUFILE=app2.ceu FLASHADDR=0x4800 all
	cd ../ && make clean && make APP=tst2/tst.c
