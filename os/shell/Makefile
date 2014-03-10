include ../one.mk

tst1:
	cd ../tst0/ && make clean && make CEUFILE=tst.ceu  FLASHADDR=0xF000 all
	cd ../gpio/ && make clean && make CEUFILE=gpio.ceu FLASHADDR=0x2000 all
	make clean
	make CEUFILE=shell.ceu FLASHADDR=0x4000 all
	make CEUFILE=tst1.ceu  FLASHADDR=0xA000 all
	cd ../tst2/ && make clean && make CEUFILE=app1.ceu FLASHADDR=0xC000 all
	cd ../tst2/ && make clean && make CEUFILE=app2.ceu FLASHADDR=0xC800 all
	cd ../ && make clean && make APP=shell/tst1.c

s2s:
	cd ../serial/ && make clean && make CEUFILE=serial.ceu FLASHADDR=0x3000 all
	make clean
	make CEUFILE=shell.ceu        FLASHADDR=0x4000 all
	make CEUFILE=serial_shell.ceu FLASHADDR=0x5000 all
	cd ../ && make clean && make APP=shell/serial_shell.c
