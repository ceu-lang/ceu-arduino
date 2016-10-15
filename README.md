Arduino binding for Céu:

https://github.com/fsantanna/ceu-arduino/

[Arduino](https://www.arduino.cc/) is an open-source electronics platform based
on easy-to-use hardware and software. It's intended for anyone making
interactive projects.

Céu is a reactive language that aims to offer a higher-level and safer
alternative to C.

Try it online:

http://www.ceu-lang.org/

Source code:

https://github.com/fsantanna/ceu/

Join our chat:

https://gitter.im/fsantanna/ceu

# INSTALLATION

## Install Arduino

https://www.arduino.cc/

## Install Céu:

https://github.com/fsantanna/ceu/

## Run the examples

Edit the `Makefile` to point to your `ceu` directory and then run `make`:

```
$ gedit Makefile
$ make
```

Certify that your Arduino is connected to the USB and that the `Makefile`
is pointing to the correct port.
The default example blinks the on-board LED every second.
