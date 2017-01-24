# Modes of Operation

A mode of operation specifies how Céu-Arduino captures events from the
environment (e.g., pin changes) and redirects them to the Céu application.

Céu-Arduino supports the *polling* and *interrupt-based* modes of operation.

The polling mode is the default mode of operation.

The modes of operation are implemented in C and are part of Céu-Arduino.
Each mode is described in pseudo-code as follows.

{!modes/polling.md!}

{!modes/interrupts.md!}
