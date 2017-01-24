## Polling

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

### Input Events

Currently, the polling mode supports the following input events:

* Timers
* Asynchronous blocks
* [Digital pins](../digital_pins/#digital-pins)

### Compilation

Since polling is the default mode of operation, compilation only needs to
provide the Céu application:

```
$ make CEU_SRC=<path-to-ceu-application>
```
