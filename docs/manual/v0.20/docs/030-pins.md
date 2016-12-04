Digital Pins
============

Céu-Arduino supports [`emit`](TODO) and [`await`](TODO) statements for digital
pins in output and input modes, respectively.

Input Pins
----------

A program can `await` a change in a digital pin configured as input and acquire
its current value:

```
input int PIN_02;
var int v = await PIN_02;
```

In the [interrupt mode](#TODO), the pin requires a driver to generate the input:
```ceu
#include "arduino/isr/pin-02.ceu"
input int PIN_02;
var int v = await PIN_02;
```

Output Pins
-----------

A program can `emit` a change to a digital pin configured as output.

### Digital Output

For digital output, the pin number requires the prefix `PIN_`:

```
output int PIN_13;
emit PIN_13(HIGH);
```

### PWM Output

For PWM output, the pin number requires the prefix `PWM_`:

```
output u8 PWM_13;
emit PWM_13(127);
```
