Céu-Arduino supports the development of Arduino applications in the programming
language Céu:

- Source Code:   https://github.com/ceu-lang/ceu-arduino/
<!-- - Documentation: http://ceu-lang.github.io/ceu-arduino/ -->
- Chat:          https://gitter.im/fsantanna/ceu

[Arduino](https://www.arduino.cc/) Arduino is an open-source project that
created microcontroller-based kits for building digital devices and interactive
objects that can sense and control physical devices.

Céu is a reactive language that aims to offer a higher-level and safer
alternative to C:

- Home Page:   http://www.ceu-lang.org/
- Source code: https://github.com/ceu-lang/ceu/

Céu-Arduino empowers the development of Arduino applications with the following
extensions:

- Awaiting events in direct/sequential style.
  <!--(e.g., timers, pin changes, serial input, etc).-->
- Parallel lines of execution with
    - safe abortion;
    - deterministic behavior (in contrast with threads).
- Asynchronous loops for heavy computations.
- Interrupt-driven operation mode (optional and experimental).
- Seamless integration with standard Arduino (e.g., `analogRead`, `random`,
  etc).

Install
=======

## Install Arduino

Requires `arduino-1.5` or higher:

https://www.arduino.cc/

## Install Céu:

https://github.com/ceu-lang/ceu/

## Clone Céu-Arduino:

```
$ git clone https://github.com/ceu-lang/ceu-arduino
$ cd ceu-arduino/
$ git checkout pre-v0.40
$ cd libraries/
$ make clone
```

## Configure:

Edit the `Makefile.conf` to point to the `ceu` repository and to set your
preferences:

```
$ gedit Makefile.conf
```

Use
===

Run `make` with the file you want to compile & upload:

```
$ make CEU_SRC=examples/blink-01.ceu
```

This example blinks the on-board LED every second.

Certify that your Arduino is connected to the USB.

Examples
========

The `examples/` directory contains a number of examples.

Blinking a LED
--------------

<!--
{{#ev:youtube|5GeGGCc7ZfM|300|right}}
Observe the behavior of the program in the video on the right.
-->

The example `blink-01.ceu` assumes that a LED is connected to *pin 13*.

The program is an infinite `loop` that intercalates between turning the LED
*on* and *off* in intervals of 1 second:

```
#include "gpio.ceu"             // uses GPIO (PIN_13)
#include "wclock.ceu"           // uses timers (await 1s)

output high/low PIN_13;         // PIN_13 is an output pin

loop do                         // an infinite loop that:
    emit PIN_13(high);          //   - turns the LED on
    await 1s;                   //   - awaits 1 second
    emit PIN_13(low);           //   - turns the LED off
    await 1s;                   //   - awaits another 1 second
end                             //   - repeats
```

<!--
- Line 3 configures `PIN_13` as an output pin.
- Lines 6,8 alternate

Just like regular Arduino programming, a pin must be configured to work in
*input* or *output* mode.
Céu uses `input` and `output` events for this purpose.

In the example, the first line configures `PIN_13` as an output pin that accepts <tt>int</tt> values.

The program is a `loop` that sets `PIN_13` to `HIGH`, awaits 1 second, sets
`PIN_13` to `LOW`, awaits another second, and repeats the process over and over.
-->

Switching a LED
---------------

<!--
{{#ev:youtube|MvAtNfcNS58|300|right}}
-->

The example `button-01.ceu` requires a simple circuit with a switch button
connected to *pin 2*.

The program waits for changes on *pin 2* (the switch), copying its value to
*pin 13* (the LED):

```
#include "gpio.ceu"
#include "pin_02.ceu"   // declares "input high/low PIN_02"

output high/low PIN_13;
emit PIN_13(_digitalRead(2));

loop do
    var high/low v = await PIN_02;
    emit PIN_13(v);
end
```

Céu can directly use standard Arduino functionality by prefixing its symbols
with an underscore (e.g., `_digitalRead(2)`).

<!--
Now, we also use an input event to read <tt>int</tt> values from <tt>PIN2</tt>.
Whenever its value changes, the command <tt>await PIN02</tt> resumes and sets
<tt>v</tt>, which is copied to <tt>PIN13</tt>.
-->

Blinking in Parallel
--------------------

<!--
{{#ev:youtube|6ZsF6X1wn84|300|right}}
-->

The example `blink-02.ceu` requires two additional LEDs connected to
*pins 11 and 12*.

The program blinks the LEDs with different frequencies, in parallel:

```
#include "gpio.ceu"
#include "wclock.ceu"

output high/low PIN_11;
output high/low PIN_12;
output high/low PIN_13;

par do
    loop do
        emit PIN_11(high);
        await 1s;
        emit PIN_11(low);
        await 1s;
    end
with
    loop do
        emit PIN_12(high);
        await 500ms;
        emit PIN_12(low);
        await 500ms;
    end
with
    loop do
        emit PIN_13(high);
        await 250ms;
        emit PIN_13(low);
        await 250ms;
    end
end
```

<!--
The <tt>par</tt> statement of Céu allows that multiple lines of execution run
concurrently in the same program.
-->

Fading a LED
------------

The example `pwm-01.ceu` assumes that a LED is connected to *pin 06*.

The program fades the LED from `0` to `255` and from `255` to `0` in two
consecutive loops:

```
#include "gpio.ceu"
#include "wclock.ceu"

output u8 PWM_06;

loop do
    var int i;
    loop i in [0->255] do
        emit PWM_06(i);
        await 5ms;
    end
    loop i in [0<-255] do
        emit PWM_06(i);
        await 5ms;
    end
end
```

Serial Echo
-----------

The example `usart-01.ceu` reads and write strings from and to the serial in a
continuous loop:

```
#include "usart.ceu"

spawn Usart(9600);

loop do
    var[20] byte str = [];
    await Usart_RX(&str, _);
    await Usart_TX(&str);
end
```

<!--
Applications
============

The Game "Ship"
---------------

The game `ship.ceu` is described in a blog post:

- https://github.com/fsantanna/ceu-arduino/blob/master/samples/ship.ceu
- http://thesynchronousblog.wordpress.com/2012/07/08/ceu-arduino/
-->
