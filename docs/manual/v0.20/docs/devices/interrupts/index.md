## Interrupt Mode Drivers

These drivers are implemented using interrupts. They provide events which enable the application to take advantadge of computing cycles using `await`s. This means that the application waits for the interrupt to notify it of the end of a reaction, using `ceu_input` calls or `code/await` abstractions.

{!devices/interrupts/analog.md!}

{!devices/interrupts/spi.md!}
