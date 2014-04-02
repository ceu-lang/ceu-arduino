tst:
	cd ../gpio/   && make CEUFILE=gpio.ceu   FLASHADDR=0x2000 all
	cd ../gpio/   && make CEUFILE=tst.ceu    FLASHADDR=0x3000 all
	cd ../serial/ && make CEUFILE=serial.ceu FLASHADDR=0x4000 all
	cd ../serial/ && make CEUFILE=tst.ceu    FLASHADDR=0x6000 all
	cd ../ && make clean && make APP=tst1/tst.c
