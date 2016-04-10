Arduino binding for Céu.

Céu is a reactive language that aims to offer a higher-level and safer 
alternative to C.

http://www.ceu-lang.org/

https://github.com/fsantanna/ceu/

[Arduino](http://www.arduino.cc/) is a platform for sensing and controlling 
physical devices:

https://github.com/fsantanna/ceu-arduino/

Join our chat at https://gitter.im/fsantanna/ceu

# Summary

* [Quick Start](#quick-start)
* [Applications](#applications)

# Quick Start

## Install `arduino`:

First, you need to install `arduino`:

```
# Ubuntu:
$ sudo apt-get install arduino

# Sources:
- Arduino: http://www.arduino.cc/
```

## Install `ceu`:

Then, you need to install `ceu`:

https://github.com/fsantanna/ceu/

## Download and Configure `ceu-arduino`:

Then, you need to download and configure `ceu-arduino`:

```
$ git clone https://github.com/fsantanna/ceu-arduino/
$ cd ceu-arduino/
```

Edit the `Makefile` to point to your `ceu` directory:

```
$ vi Makefile
CEU_DIR ?= <path to "ceu" repository>  # EDIT THIS LINE
```

Run `make link` to properly point to your `ceu` repository:

```
$ make link
```

## Run the examples

<!--
First, try the `poll` binding:

```
$ cd poll/
```
-->

Now, you are ready to run the examples.

```
$ make samples
for i in samples/*.ceu; do								\
		echo;									\
		echo -n "#####################################";		\
		echo    "#####################################";		\
		echo File: "$i";							\
		grep "#@" "$i" | cut -f2- -d" ";					\
		echo -n "#####################################";		\
		echo    "#####################################";		\
		echo -n "Press <enter> to start...";					\
		read _;									\
		if [ "$i" = "samples/test-03.ceu" ]; then				\
			make ARCH_DIR=arch/pthread SRC=$i all || exit 1;	\
		else									\
			make SRC=$i all || exit 1;					\
		fi;									\
		echo;									\
	done

##########################################################################
File: samples/blink-01.ceu
##########################################################################
Press <enter> to start...
```

<!--
After testing `poll`, try also the `isr` binding:

```
$ cd ../isr/
$ make samples
```
-->

# Applications

TODO
