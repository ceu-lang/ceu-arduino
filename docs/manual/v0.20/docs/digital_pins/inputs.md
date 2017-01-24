## Input Pins

A program can `await` a change in a digital pin configured as input and acquire
its current value:

```
input int PIN_02;
var int v = await PIN_02;
```

In the [interrupt mode](../modes/#interrupts), the pin requires a driver to
generate the input:

```ceu
#include "arduino/isr/pin-02.ceu"
input int PIN_02;
var int v = await PIN_02;
```
