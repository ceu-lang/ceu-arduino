# SPI

Céu-Arduino provides SPI configuration and byte transfers using input and output events as well as `code/await` abstractions which encapsulate the procedures.

This driver used pins 10, 11, 12 and 13 for the Arduino Uno, as they are SS, MOSI, MISO and SCLK, respectively.

## Output Events

### SPI_BEGIN

```ceu
output (none) SPI_BEGIN
```

Enables the SPI module. Needs to be emitted before any SPI operation.

The example below enables the SPI module:

```ceu
...
emit SPI_BEGIN;
...
```
### SPI_END

```ceu
output (none) SPI_END
```

Disables the SPI module in case no other device is using it.

The example below enables the SPI module from two different parts of the code and then disable it at different times:

```ceu
...
par/and do
    emit SPI_BEGIN;
    await 1s;
    emit SPI_END;
with
    emit SPI_BEGIN;
    await 10s;
    emit SPI_END;
end
...
```

The module is only trully disabled after 10s in this example.

### SPI_TRANSACTION_BEGIN

```ceu
output (freq,bitOrder,dataMode) SPI_TRANSACTION_BEGIN;
```

- Parameters:
    - `freq` | `u32` : frequency the SPI clock will operate in
    - `bitOrder` | `u8` : Order in which bits will be shifted in. Possible values are `_MSBFIRST` and `_LSBFIRST`, for Most Significant Bit First and Least Significant Bit First. More information [here](https://en.wikipedia.org/wiki/Most_significant_bit#Most_Significant_Bit_First_vs_Least_Significant_Bit_First).
    - `dataMode` | `u8` : SPI mode of operation. Possible values are `_SPI_MODE0`, `_SPI_MODE1`, `_SPI_MODE2`, `_SPI_MODE3`. More information [here](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers). 

Gets control of the driver while configuring it. Has to be called before transfering any bytes. It's the users responsability to not emit a subsequent `SPI_TRANSACTION_BEGIN` before emitting a correspondent [`SPI_TRANSACTION_END`](#spi_transaction_end).

The example below gets control of the driver for 10 seconds, with the configuration of 1400000 Hz, Most Significant Bit First and SPI Mode of Operation "0":

```ceu
...
emit SPI_BEGIN;
emit SPI_TRANSACTION_BEGIN(1400000,_SPI_MSBFIRST,_SPI_MODE0);
await 10s;
emit SPI_TRANSACTION_END;
...
```

### SPI_TRANSACTION_END

```ceu
output (none) SPI_TRANSACTION_END
```

Yeilds control of the driver. Has to be called before a subsequent emit to [`SPI_TRANSACTION_BEGIN`](#spi_transaction_begin). Failing to do so will cause the application to crash.

### SPI_TRANSFER_REQUEST

```ceu
output (value?) SPI_TRANSFER_REQUEST;
```

- Parameters:
    - `value` | `u8?` : Byte to transmit to slave.
    
Starts a transfer, transmitting `value` if passed as a parameter. It is the responsability of the application to not call a subsequent `SPI_TRANSFER_REQUEST` before the driver emits the correspondent [`SPI_TRANSFER_DONE`](#spi_transfer_done).

The example below transmits a byte to the slave:

```ceu
...
emit SPI_BEGIN;
emit SPI_TRANSACTION_BEGIN;
var u8 value = 0xAB;
emit SPI_TRANSFER_REQUEST(value);
await SPI_TRANSFER_DONE;
emit SPI_TRANSACTION_END;
emit SPI_END;
...
``` 

## Input Events

### SPI_TRANSFER_DONE

```ceu
input (u8) SPI_TRANSFER_DONE;
```

Marks the end of a byte transfer, returning the byte received from the slave.

The example below reads a byte from the slave:

```ceu
...
emit SPI_BEGIN;
emit SPI_TRANSACTION_BEGIN;
emit SPI_TRANSFER_REQUEST(_);
var u8 recv = await SPI_TRANSFER_DONE;
emit SPI_TRANSACTION_END;
emit SPI_END;
...
``` 
## Internal Events

### spi_transaction_done

```ceu
event none spi_transaction_done;
```

Marks the end of a transaction. Used internally by the driver for synchronization.

## Code/Await Abstractions

### SPI_Begin

```ceu
code/await SPI_Begin (none) -> none  do
    emit SPI_BEGIN;
    do finalize with
        emit SPI_END;
    end
    await FOREVER;
end
```

Enables the SPI module.

The example below enables the SPI module for 10 seconds:

```ceu
watching SPI_Begin do
    await 10s;
end
```

As the watching block reaches the end of execution, the `do finalize with` block in the code/await abstraction executes, disabling the module.

### SPI_Transaction

```ceu
code/await SPI_Transaction (var u32 freq, var u8 byte_order, var u8 mode) -> none do
    if outer.spi_transaction_busy then
        await outer.spi_transaction_end until outer.spi_transaction_busy == false;
    end
    emit SPI_TRANSACTION_BEGIN(freq,byte_order,mode);
    do finalize with
        emit SPI_TRANSACTION_END;
        emit outer.spi_transaction_end;
    end
    await FOREVER;
end
```
- Parameters:
    - `freq` | `u32` : frequency the SPI clock will operate in
    - `bit_order` | `u8` : Order in which bits will be shifted in. Possible values are `_MSBFIRST` and `_LSBFIRST`, for Most Significant Bit First and Least Significant Bit First. More information [here](https://en.wikipedia.org/wiki/Most_significant_bit#Most_Significant_Bit_First_vs_Least_Significant_Bit_First).
    - `mode` | `u8` : SPI mode of operation. Possible values are `_SPI_MODE0`, `_SPI_MODE1`, `_SPI_MODE2`, `_SPI_MODE3`. More information [here](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers)

Gets control of the driver while configuring it. In case the driver is busy, awaits until can get control of driver.

The example below gets control of the driver for 10 seconds, with the configuration of 1400000 Hz, Most Significant Bit First and SPI Mode of Operation "0":

```ceu
...
watching SPI_Begin() do
    watching SPI_Transaction(1400000,_SPI_MSBFIRST,_SPI_MODE0) do
        await 10s;
    end
end
...
```

Similar to [`SPI_Begin`](#spi_begin), when the watching block reaches the end of execution, the `do finalize with` block in the code/await abstraction executes, yielding control of the driver.

### SPI_Transfer

```ceu
code/await SPI_Transfer (var u8? value) -> u8 do
    if value? == true then
        emit SPI_TRANSFER_REQUEST(value!);
    else
        emit SPI_TRANSFER_REQUEST(_);
    end
    var u8 recv = await SPI_TRANSFER_DONE;
    escape recv;
end
```

- Parameters:
    - `value` | `u8?` : Byte to transmit to slave.
    
Starts a transfer, transmitting `value` if passed as a parameter and returning the value received from the slave.

The example below transmits a byte to the slave and reads what was received:

```ceu
...
watching SPI_Begin() do
    watching SPI_Transaction(1400000,_SPI_MSBFIRST,_SPI_MODE0) do
        var u8 recv = await SPI_Transfer(0xAB);
    end
end
...
```
