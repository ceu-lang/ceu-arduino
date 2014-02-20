CEUDIR ?= /data/ceu/ceu-arduino

#ARDUINOSUB = arduino
#BOARD = uno
ARDUINOSUB ?= Microduino
BOARD ?= 644pa16m
#lilypad328
#uno

INCLUDES += -I $(CEUDIR)/os
CPPFLAGS += $(INCLUDES)
CPPFLAGS += -mrelax -DCEU_OS

ifndef CEUFILE
$(error missing CEUFILE application)
endif

OBJECT = $(addprefix _ceu_, $(addsuffix .o, $(basename $(CEUFILE))))
TARGET = $(basename $(OBJECT))
FLASHADDR ?= 0x00

_comma := ,
LINKFLAGS += $(addprefix -Wl$(_comma)-u, $(addsuffix _SIZE, $(basename $(CEUFILE))))
LINKFLAGS += $(addprefix -Wl$(_comma)-u, $(addsuffix _init, $(basename $(CEUFILE))))
#LIBS    +=

.PHONY:	all target flash

target: $(OBJECT)

all: target upload

upload: _upload

.SECONDARY:		# keeps _ceu_xxx.c
_ceu_%.c: %.ceu
	ceu $< 	--os --verbose \
			--out-c $@ \
			--out-h $(basename $@).h \
			--out-s $(basename $<)_SIZE \
			--out-f $(basename $<)_init \
			--cpp-args "$(INCLUDES)"

_ceu_%.o: _ceu_%.c $(LIBS)
	$(CC) $(CPPFLAGS) $(LINKFLAGS) \
		-nostartfiles \
		$^ -o $@
	#$(STRIP) -s $@
	$(AVRSIZE) $@
	$(OBJCOPY) --change-addresses=$(FLASHADDR) -O ihex $@ $(TARGET).hex

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
