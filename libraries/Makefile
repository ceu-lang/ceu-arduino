BRANCH = pre-v0.40

LIBRARIES = arch-avr arch-samd driver-adc driver-gpio driver-hcsr04 driver-i2c \
            driver-nrf24l01 driver-pm driver-spi driver-rtc driver-mfs \
            driver-usart driver-wclock driver-wdt #protocol-rf24network

all:
	$(error Choose target...)

clone:
	for i in $(LIBRARIES); do                          \
	    echo;                                          \
	    echo ">>> $$i";                                \
	    git clone https://github.com/ceu-arduino/$$i;  \
	    cd "$$i";                                      \
	    git checkout $(BRANCH);                        \
	    cd -;                                          \
	done

branch:
	for i in $(LIBRARIES); do               \
	    echo;                               \
	    echo ">>> $$i";                     \
	    cd "$$i";                           \
	    git branch $(BRANCH);               \
	    git checkout $(BRANCH);             \
	    cd -;                               \
	done

pull:
	for i in $(LIBRARIES); do               \
	    echo;                               \
	    echo ">>> $$i";                     \
	    cd "$$i";                           \
	    git pull;                           \
	    cd -;                               \
	done

push:
	for i in $(LIBRARIES); do               \
	    echo;                               \
	    echo ">>> $$i";                     \
	    cd "$$i";                           \
	    git push origin $(BRANCH);          \
	    cd -;                               \
	done
