###############################################################################
# EDIT
###############################################################################

ARD_EXE    = /opt/arduino-1.6.8/arduino
#ARD_EXE   = arduino
ARD_ARCH   ?= avr
ARD_BOARD  ?= uno
#ARD_BOARD ?= mega
#ARD_CPU   ?= :cpu=atmega328p
ARD_PORT   ?= /dev/ttyACM0

ARD_FLAGS += --verbose
#ARD_FLAGS += --preserve-temp-files		# only Arduino >= 1.6?

###############################################################################
# DO NOT EDIT
###############################################################################

# ceu_main.c needs to be renamed to x.ino, where x must equal to OUT_DIR
ARD_INO = $(OUT_DIR)/$(OUT_DIR).ino

#C_FLAGS += -DHardwareSerial_h	# only for ISR
C_FLAGS_ += -I$(ARCH_DIR)
C_FLAGS_ := --pref compiler.cpp.extra_flags="$(C_FLAGS_)"

CEU_FLAGS += --safety 2
CEU_FLAGS += --out-c _ceu_app.c.h

all: ceu c
	:	# nop

c:
	cp $(ARCH_DIR)/ceu_main.c $(ARD_INO)
	$(ARD_EXE) $(ARD_FLAGS) $(C_FLAGS_) \
			   --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU) \
			   --port $(ARD_PORT) --upload $(ARD_INO)

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
