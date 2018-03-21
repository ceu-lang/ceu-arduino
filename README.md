Céu-Arduino supports the development of Arduino applications in the programming
language Céu:

- Source Code:   https://github.com/fsantanna/ceu-arduino/
- Documentation: http://fsantanna.github.io/ceu-arduino/
- Chat:          https://gitter.im/fsantanna/ceu

[Arduino](https://www.arduino.cc/) Arduino is an open-source project that
created microcontroller-based kits for building digital devices and interactive
objects that can sense and control physical devices.

Céu is a reactive language that aims to offer a higher-level and safer
alternative to C:

- Home Page:   http://www.ceu-lang.org/
- Source code: https://github.com/fsantanna/ceu/

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

https://github.com/fsantanna/ceu/

## Clone Céu-Arduino:

```
$ git clone https://github.com/fsantanna/ceu-arduino
$ cd ceu-arduino/
$ git checkout v0.30
```

## Compile and Upload

Edit the `Makefile` to point to your `ceu` directory and then run `make`:

```
$ gedit Makefile
$ make
```

Certify that your Arduino is connected to the USB.
If necessary, configure the variables in the `Makefile`.
The default example blinks the on-board LED every second.

To compile and upload another application, run `make` and set `CEU_SRC`:

```
$ make CEU_SRC=<path-to-ceu-application>
```

Examples
========

The `samples/` directory contains a number of examples.

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
#include "arduino/arduino.ceu"  // include standard declarations

output int PIN_13;              // PIN_13 is an output pin

loop do                         // an infinite loop that:
    emit PIN_13(HIGH);          //   - turns the LED on
    await 1s;                   //   - awaits 1 second
    emit PIN_13(LOW);           //   - turns the LED off
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
#include "arduino/arduino.ceu"

input  int PIN_02;
output int PIN_13;

emit PIN_13(LOW);

loop do
    var int v = await PIN_02;
    emit PIN_13(v);
end
```

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

The example `blink-03.ceu` requires two additional LEDs connected to
*pins 11 and 12*.

The program blinks the LEDs with different frequencies, in parallel:

```
#include "arduino/arduino.ceu"

output int PIN_11;
output int PIN_12;
output int PIN_13;

par do
    loop do
        emit PIN_11(HIGH);
        await 1s;
        emit PIN_11(LOW);
        await 1s;
    end
with
    loop do
        emit PIN_12(HIGH);
        await 500ms;
        emit PIN_12(LOW);
        await 500ms;
    end
with
    loop do
        emit PIN_13(HIGH);
        await 250ms;
        emit PIN_13(LOW);
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

The example `pwm-01.ceu` assumes that a LED is connected to *pin 11*.

The program fades the LED from `0` to `255` and from `255` to `0` in two
consecutive loops:

```
#include "arduino/arduino.ceu"

output u8 PWM_11;

loop do
    var int i;
    loop i in [0->255] do
        emit PWM_11(i);
        await 5ms;
    end
    loop i in [0<-255] do
        emit PWM_11(i);
        await 5ms;
    end
end
```

Serial Echo
-----------

The example `serial-01.ceu` reads and write bytes from and to the serial in a
continuous loop:

```
#include "arduino/arduino.ceu"

input byte SERIAL;

loop do
    var byte c = await SERIAL;
    _Serial.write(c);
end
```

Céu can directly use standard Arduino functionality by prefixing its symbols
with an underscore (e.g., `_Serial.write(c)`).

Switching a LED with Interrupts
-------------------------------

The example `isr-01.ceu` is equivalent to `button-01.ceu` but uses interrupts
instead of polling:

```
#include "arduino/arduino.ceu"

input  int PIN_02;
output int PIN_13;

spawn async/isr [_digitalPinToInterrupt(2),_CHANGE] do
    emit PIN_02(_digitalRead(2));
end

emit PIN_13(LOW);

loop do
    var int v = await PIN_02;
    emit PIN_13(v);
end
```

The `async/isr` is an interrupt service routine written in Céu.
It is attached to the interrupt number for *pin 2*
(`_digitalPinToInterrupt(2)`) and is triggered whenever the pin changes value
(`_CHANGE`).
The routine emits a `PIN_02` input to the application.

Examples that use interrupts have to be compiled with `CEU_ISR=true`:

```
make CEU_ISR=true CEU_SRC=samples/isr-01.ceu
```

Interrupts with Drivers
-----------------------

The example `isr-08.ceu` uses the interrupt drivers `timer.ceu` and
`pin-02.ceu` from the library.

The program blinks the LED connected to *pin 13* until the button connected to
*pin 02* is clicked.
After another click, the blinking restarts.

```
#include "arduino/isr/timer.ceu"        // timer ISR
#include "arduino/isr/pin-02.ceu"       // pin-02 ISR

output int PIN_13;

loop do
    watching PIN_02 do                  // aborts on click
        var int x = 0;
        every 500ms do                  // blinks every 500ms
            x = 1 - x;
            emit PIN_13(x);
        end
    end
    await 500ms;                        // debouncing
    await PIN_02;                       // restarts
    await 500ms;                        // debouncing
end
```

Applications
============

The Game "Ship"
---------------

The game `ship.ceu` is described in a blog post:

- https://github.com/fsantanna/ceu-arduino/blob/master/samples/ship.ceu
- http://thesynchronousblog.wordpress.com/2012/07/08/ceu-arduino/

<!--
[[http://www.ceu-lang.org/downloads/ceu_arduino_current.tgz download]] The current version of Céu for Arduino.

The Céu compiler requires [[Lua]] and [[LPeg]] installed.

We assume you are using a Linux-like programming environment.

After downloading Céu for Arduino, unpack it, adjust the <tt>Makefile</tt>, and run <tt>make</tt>:

    $ tar xvzf ceu_arduino_*.tgz
    $ cd ceu_arduino_*
    $ vi Makefile
    $ make

You should see the LED on PIN13 blinking, just like in the video on the right.

By default, Céu uses the file <tt>samples/blink1.ceu</tt>, as defined in the Makefile.
However, it's possible to pass different files to <tt>make</tt>.

== Project Files ==

Céu requires two files to generate your application:
* <tt>INOFILE</tt>: a binding to C (.pde)
* <tt>CEUFILE</tt>: the actual Céu program (.ceu)

By default, Céu uses the files <tt>poll.pde</tt> and <tt>samples/blink1.ceu</tt>, as defined in the Makefile.
However, it's possible to pass different files to <tt>make</tt>:

    $ make INOFILE=async.pde CEUFILE=samples/blink1_async.ceu

== C Binding ==

The C binding is more complex to write, but fortunately, requires just a few adjustments from project to project.

The default binding <tt>poll.pde</tt> uses a polling mechanism to generate events to Céu.

Follows a simplified version of the file:

    void setup ()
    {
        pinMode(2, INPUT);              // this project uses pin 2 as input
        ceu_go_init(millis());          // initializes Ceu with the current time
    }

    int p2;                             // current value of pin 2

    void loop()
    {
        // generates the events related to pin 2
        int tmp = digitalRead(2);
        if (p2 != tmp) {                // pin 2 has changed
            p2 = tmp;
            if (p2==HIGH)
                ceu_go_event(IO_PIN2_HIGH, NULL);
            else
                ceu_go_event(IO_PIN2_LOW, NULL);
            ceu_go_event(IO_PIN2, (void*)p2);
        }

        delay(POLLING_INTERVAL);        // saves CPU
        ceu_go_time(millis());          // generates time for Ceu
    }

When creating a new project, just copy <tt>poll.pde</tt> and make the changes according to the new configuration of pins.

== What's next? ==

* Examples in the <tt>samples/</tt> directory.
* [[Tutorial]] on Céu.

Did you like Céu?
Would you like to use it?
Please, let me know, I can help you!

http://www.lua.inf.puc-rio.br/~francisco

-->
