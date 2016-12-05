Serial
======

Céu-Arduino supports [`emit`](TODO) and [`await`](TODO) statements for the
serial port.

Polling Mode
------------

A program can `await` incoming bytes from the serial as follows:

```
input byte SERIAL;
var byte c = await SERIAL;
```

The macro `CEU_ARDUINO_SERIAL_SPEED` specifies the data transmission speed
(it defaults to `9600`).

In the polling mode, writing to the serial is the same as in Arduino:

https://www.arduino.cc/en/Reference/Serial

Note that variable and function names from Arduino must be prefixed with an
underscore to be used from Céu (e.g., `_Serial.write()`).

Interrupt Mode
--------------

`TODO`
