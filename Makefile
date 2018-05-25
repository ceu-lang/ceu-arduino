include Makefile.conf

# make ARD_BOARD=mega ARD_CPU=atmega2560    ARD_PORT=/dev/ttyACM1 CEU_SRC=...
# make ARD_BOARD=pro  ARD_CPU=8MHzatmega328 ARD_PORT=/dev/ttyUSB0 CEU_SRC=...

ifndef CEU_SRC
$(error missing `CEU_SRC` path to compile)
endif

INO_SRC ?= env/env.ino

PRESERVE = --preserve-temp-files

ARD_ARCH_UPPER  = $(shell echo $(ARD_ARCH)  | tr a-z A-Z)
ARD_CPU_UPPER   = $(shell echo $(ARD_CPU)   | tr a-z A-Z)
ARD_BOARD_UPPER = $(shell echo $(ARD_BOARD) | tr a-z A-Z)

LIBRARIES = $(sort $(dir $(wildcard libraries/*/)))
CEU_INCS  = $(addprefix -I./, $(addsuffix $(ARD_ARCH)/$(ARD_BOARD)/$(ARD_CPU), $(LIBRARIES))) \
            $(addprefix -I./, $(addsuffix $(ARD_ARCH)/$(ARD_BOARD), $(LIBRARIES)))            \
            $(addprefix -I./, $(addsuffix $(ARD_ARCH), $(LIBRARIES)))                         \
            $(addprefix -I./, $(LIBRARIES))

ifdef ARD_CPU
	ARD_CPU_ = :cpu=$(ARD_CPU)
endif

#CEU_DEFS = -DCEU_PM
#CC_DEFS = -DCEU_PM_MIN
ARD_PREFS = --pref compiler.cpp.extra_flags="$(CEU_DEFS) $(CC_DEFS)"

all: ceu c

c:
	$(ARD_EXE) --verbose $(PRESERVE) $(ARD_PREFS)                              \
	           --board arduino:$(ARD_ARCH):$(ARD_BOARD)$(ARD_CPU_)             \
	           --port $(ARD_PORT)                                              \
	           --upload $(INO_SRC)

ceu:
	ceu --pre --pre-args="-include ./include/arduino/arduino.ceu -include ./libraries/arch-$(ARD_ARCH)/$(ARD_ARCH).ceu -I$(CEU_DIR)/include/ -I./include/ $(CEU_INCS) $(CEU_DEFS) -DCEUMAKER_ARDUINO -DARDUINO_ARCH_$(ARD_ARCH_UPPER) -DARDUINO_MCU_$(ARD_MCU_UPPER) -DARDUINO_BOARD_$(ARD_BOARD_UPPER)" \
	          --pre-input=$(CEU_SRC)                                           \
	    --ceu --ceu-err-unused=pass --ceu-err-uninitialized=pass               \
	          --ceu-line-directives=true                                       \
	          --ceu-features-lua=false --ceu-features-thread=false             \
	          --ceu-features-callbacks=static --ceu-features-isr=static        \
	    --env --env-types=env/types.h                                          \
	          --env-output=env/_ceu_app.c.h

pre:
	ceu --pre --pre-args="-include ./include/arduino/arduino.ceu -include ./libraries/arch-$(ARD_ARCH)/$(ARD_ARCH).ceu -I$(CEU_DIR)/include/ -I./include/ $(CEU_INCS) $(CEU_DEFS) -DCEUMAKER_ARDUINO -DARDUINO_ARCH_$(ARD_ARCH_UPPER) -DARDUINO_MCU_$(ARD_MCU_UPPER) -DARDUINO_BOARD_$(ARD_BOARD_UPPER)" --pre-input=$(CEU_SRC)

.PHONY: all ceu
