Modes
=====

Céu-Arduino supports the *polling* and *interrupt* modes of operation.

Polling Mode
------------

The *polling mode* of Céu-Arduino continually checks for changes in the
environment in an infinite loop.

```c
void loop ()
{
    while (<program-is-running>)
    {
        /* ASYNC */
        if (<program-has-pending-async>) {
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }

        /* WCLOCK */
        ceu_input(CEU_INPUT__WCLOCK, &dt);

        /* PINS */
        if (<pin-*-changes>) {
            ceu_input(CEU_INPUT__PIN_*, &dt);
        }
        <...>   // for each pin
    }
    while (1);
}
```

- 100% cpu


Polling is the default mode of operation of Céu-Arduino.

### Compilation

Examples that use interrupts have to be compiled with `CEU_ISR=true`:

```
make CEU_ISR=true CEU_SRC=samples/isr-01.ceu
```

Interrupt Mode
--------------

The *interrupt mode* of Céu-Arduino .

- [a,b]
- scope
