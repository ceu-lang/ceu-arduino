## Output Pins

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
