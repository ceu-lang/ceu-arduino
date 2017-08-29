# Analog to Digital Converter

Céu-Arduino provides asynchronous reads of analog values. This driver provides users with events and a data structure for full control of the driver as well as an abstraction which encapsulates the procedure.

## Output Events

### ADC_REQUEST

```ceu
output (pin) ADC_REQUEST
```

- Parameters:
    - `pin` | `integer` : pin to queue read

Queues an analog read for the specified analog pin.

The example below starts a conversion for `A0`:

```ceu
...
emit ADC_REQUEST(0);
...
```

## Input Events

### ADC_DONE

```ceu
input (none) ADC_DONE
```

Marks the end of a read. Can be used for synchronization.

The example below keeps a LED connected to `PIN_01` on while the read is in progress:

```ceu
...
emit ADC_REQUEST(1);
emit PIN_01(on);
await ADC_DONE;
emit PIN_01(off);
...
```

## Data Abstractions

There is a data structure which carries all information about the read state for each pin. The structure is a vector of [`ADC_Channel`](#adc_channel) named `channels`. There is an instance of [`ADC_Channel`](#adc_channel) in `channels` for each analog read pin available on the board (5 for the Arduino Uno).

### ADC_Channel

```ceu
data ADC_Channel with
    var bool is_available = false;
    var bool is_busy      = false;
    var int  value;
end
```

- Fields:
    - `is_available` : Whether or not there is read value available
    - `is_busy` : Whether or not a read is in progress
    - `value` : Value of latest conversion, in case `is_available` is set

This data structure carries all information about a pin read state. It should be used to get the actual value of the read and to monitor the state of the conversion.

The `is_available` flag is only set when a conversion is done for that pin. Since [`ADC_DONE`](#adc_done) is emitted at the end of every conversion, the flag provides a way to differentiate between conversion results.

**Clearing the flag is the user's responsability.**

The `is_busy` flag is for the driver's internal usage. It asserts that there are not more than one [`await Analog()`](#analog) for the same pin at a same given time. 

**If the application enters two [`await Analog()`](#analog) simultaneously, the application will raise an error**

The example below reads the conversion value for pin `A2`:

```ceu
...
emit ADC_REQUEST(2);
await ADC_DONE;
var int recv = channels[2].value;
...
```
The code below provides a safer alternative to the code above since it deals with simultaneous reads:

```ceu
...
emit ADC_REQUEST(2);
await ADC_DONE until channels[2].is_available;
var int recv = channels[2].value;
channels[2].is_available = false;
...
```

## Code/Await Abstractions

### Analog

Performs a full analog read.

```ceu
code/await Analog (var int channel) -> int do
    _ceu_dbg_assert(outer.channels[channel].is_busy == false);
    outer.channels[channel].is_busy = true;
    do finalize with
        outer.channels[channel].is_busy = false;
    end
    emit ADC_REQUEST(channel);
    await ADC_DONE until outer.channels[channel].is_available;
    outer.channels[channel].is_available = false;
    escape outer.channels[channel].value;
end
```

- Parameters:
    - `channel` : analog pin for which to perform the read

The example below reads the value from analog pins 3 and 4, concurrently:

```ceu
...
par/and do
    var int recv_3 = await Analog(3);
with
    var int recv_4 = await Analog(4);
end
...
```
