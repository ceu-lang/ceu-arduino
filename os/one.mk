CEUDIR ?= /data/ceu/ceu-arduino

#ARDUINOSUB = arduino
#BOARD = uno
#BOARD = lilypad328
ARDUINOSUB ?= Microduino
BOARD ?= 644pa16m

CPPFLAGS += -DCEU_OS -I $(CEUDIR)/os
CPPFLAGS += -mrelax -mshort-calls #-mcall-prologues -fpic
#CPPFLAGS += -I/opt/arduino/hardware/Microduino/variants/plus/
#CPPFLAGS += -imultilib avr5 -iprefix
#CPPFLAGS += /opt/arduino-1.0.5/hardware/tools/avr/bin/../lib/gcc/avr/4.3.2/

ifndef CEUFILE
#$(error missing CEUFILE application)
endif

OBJECT = $(addprefix _ceu_, $(addsuffix .o, $(basename $(CEUFILE))))
TARGET = $(basename $(OBJECT))
FLASHADDR ?= 0x00

LINKFLAGS += -Wl,--section-start=.export=0x00 \
			 -Wl,--section-start=.text=0x16   \
			 -Wl,-uCEU_EXPORT
# TODO: 0x16 is hardcoded (size of CEU_EXPORT)

.PHONY:	all target flash

target: $(OBJECT)

all: target upload

upload: _upload

.SECONDARY:		# keeps _ceu_xxx.c
_ceu_%.c: %.ceu
	ceu $< 	--os --verbose \
			--out-c $@ \
			--cpp-exe "$(CPP)" \
			--cpp-args "$(CPPFLAGS)"
#--out-h $(basename $@).h
#--out-s $(basename $<)_SIZE
#--out-f $(basename $<)_init

_ceu_%.o: _ceu_%.c $(LIBS)
	$(CC) $(CPPFLAGS) $(LINKFLAGS) \
		-nostartfiles \
		$^ -o $@
	! $(OBJDUMP) -h $@ | fgrep ".data"
	#$(STRIP) -s $@
	$(AVRSIZE) $@
	$(OBJCOPY) --change-addresses=$(FLASHADDR) -O ihex $@ $(TARGET).hex
	$(SRECCAT) $(TARGET).hex -intel -o $(TARGET).srec
	$(SRECCAT) $(TARGET).srec -o $(TARGET).hex -intel

# WORKAROUND: OBJDUMP generates a difficult HEX to parse.
#             SRECCAT does HEX => SREC => HEX (easy one)

#-nostartfiles -nodefaultlibs -nostdlib
#$(LINKFLAGS)
#$(COMPILE.c) -c -o $(APP).o $(APP).c
#$(CC) -Os -Wl,--gc-sections -mmcu=atmega644p $(APP).o _arduino.a -o $(APP).elf
#$(LD) -Ttext=$(APPTEXT) -o $(APP).elf $(APP).o _arduino.a

clean: _clean
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f
	find . -name "*.hex"  | xargs rm -f
	find . -name "*.o"    | xargs rm -f

include $(CEUDIR)/arduino.mk
