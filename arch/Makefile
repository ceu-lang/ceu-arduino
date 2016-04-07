#ARDUINO ?= arduino
#ARDUINO = /opt/arduino-1.5.8/arduino
ARDUINO = /opt/arduino-1.6.6/arduino
#ARDUINO = /opt/arduino-1.6.8/arduino

ARCH ?= avr

BOARD ?= uno
#BOARD ?= mega
#BOARD = lilypad328
#BOARD = Microduino
#BOARD = 644pa16m

#CPU ?= :cpu=atmega328p
#CPU ?= :cpu=atmega168

PORT ?= /dev/ttyACM0

# only Arduino >= 1.6?
PRESERVE = --preserve-temp-files

#CFLAGS += -DHardwareSerial_h	# only for ISR
CFLAGS += -I$(ARCH_DIR)
CFLAGS := --pref compiler.cpp.extra_flags="$(CFLAGS)"

CEU_FLAGS += --safety 2
CEU_FLAGS += --out-c _ceu_app.c.h

# main.c needs to be renamed to x.ino, where x must equal to OUT_DIR
INO = $(OUT_DIR)/$(OUT_DIR).ino;

all: compiler ceu
	cp $(ARCH_DIR)/main.c $(INO)
	$(ARDUINO) --verbose $(PRESERVE) $(CFLAGS) \
			   --board arduino:$(ARCH):$(BOARD)$(CPU) \
			   --port $(PORT) --upload $(INO)

c:
	cp $(ARCH_DIR)/main.c $(INO)
	$(ARDUINO) --verbose $(PRESERVE) $(CFLAGS) \
			   --board arduino:$(ARCH):$(BOARD)$(CPU) \
			   --port $(PORT) --verify $(INO)

clean:
	rm -rf $(OUT_DIR)/
	rm -Rf /tmp/build*

### SIM ###
sim: sim-ceu ino _all
sim-ceu:
	ceu --timemachine --cpp-args "-I . -DCEUFILE=$(CEUFILE)" sim.ceu --out-c _ceu_app.src
sim-tst: sim-tst-ceu ino _all
sim-tst-ceu:
	ceu --timemachine --cpp-args "-I ." sim-tst.ceu --out-c _ceu_app.src
###

#CPPFLAGS += -Wno-pointer-arith -Wno-unused-label
#LINKFLAGS += -Wl,--section-start=.bootloader=0xE000
