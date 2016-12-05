Modes of Operation
==================

Céu-Arduino supports the *polling* and *interrupt-based* modes of operation.

Polling Mode
------------

The *polling mode* of Céu-Arduino continually checks for changes in the
environment in an infinite loop:

```c
void setup () {
    ceu_start();
    while (<program-is-running>) {
        ceu_input(CEU_INPUT__NONE, NULL, <time>);   /* input async and timer */
        if (<pin-*-changed>) {
            ceu_input(CEU_INPUT__PIN_*, <...>);     /* input pins */
        }
        <...>   // for each pin
    }
    ceu_stop();
    while (1);                                      /* freezes arduino */
}

void loop () { /* never reached */ }
```

The inputs are polled on each loop iteration and changes are notified to the
Céu application through `ceu_input` calls.

The polling mode uses *100%* of the CPU time.

The polling mode is the default mode of operation of Céu-Arduino.

### Input Events

Currently, the polling mode supports the following input events:

* [timer](TODO)
* [async](TODO)
* [digital pins](#TODO)

### Compilation

Since polling is the default mode of operation, compilation only needs to
provide the Céu application:

```
$ make CEU_SRC=<path-to-ceu-application>
```

Interrupt-Base Mode
-------------------

In the *interrupt-based mode* of Céu-Arduino, all input is done in Céu itself
through [`async/isr` blocks](TODO).
Emitting an input event from an `async/isr` only sets a flag which is then
checked in the Arduino loop:

```c
void setup () {
    ceu_start();
    while (<program-is-running>) {
        ceu_input(CEU_INPUT__NONE, NULL, CEU_WCLOCK_INACTIVE);
        if (<any-isr-evt-occurred>) {               // interrupts off
            ceu_input(<isr-evt-occuring>, <...>);   // interrupts on
        }
#ifdef CEU_FEATURES_ISR_SLEEP
        else if (!<program-has-pending-async>) {
            <enter-sleep-mode>
        }
#endif
    }
    ceu_stop();
    while (1);                                      /* freezes arduino */
}

void loop () { /* never reached */ }
```

To comply with the synchronous semantics of Céu, all `ceu_input` calls are
serialized in the loop.

If the macro `CEU_FEATURES_ISR_SLEEP` is defined, the Arduino enters in the
`SLEEP_MODE_IDLE`
[sleep mode](http://playground.arduino.cc/Learning/ArduinoSleepCode)
after each reaction.

Interrupts are disabled only while checking for occurring inputs.
Hence, `async/isr` blocks and synchronous code may be concurrent and require
[`atomic` blocks](TODO).

An `async/isr` in Céu-Arduino requires two arguments:

- the interrupt number (i.e., the index in the interrupt vector)
- the interrupt trigger mode (i.e., when the interrupt should be triggered)

The interrupt trigger mode is only used for digital pin interrupts:

<https://www.arduino.cc/en/Reference/AttachInterrupt>

The example that follows executes the code marked as `<...>` whenever the value
of *pin 2* changes:

```
spawn async/isr [_digitalPinToInterrupt(2),_CHANGE] do
    <...>
end
```

### Input Events

Drivers:

- [`pin-02`](https://github.com/fsantanna/ceu-arduino/blob/master/include/arduino/isr/pin-02.ceu):
    `TODO`
- [`timer`](https://github.com/fsantanna/ceu-arduino/blob/master/include/arduino/isr/timer.ceu):
    `TODO`
- [`usart`](https://github.com/fsantanna/ceu-arduino/blob/master/include/arduino/isr/usart.ceu):
    `TODO`

### Compilation

Applications that use interrupts have to be compiled with `CEU_ISR=true`:

```
$ make CEU_ISR=true CEU_SRC=<path-to-ceu-application>
```

