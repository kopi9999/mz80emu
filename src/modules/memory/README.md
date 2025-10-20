# memory module

## Function

This module emulates 64 KiB ram.

### `strobeUp` function

On strobe up chip select signal is checked for read/write requests. If one is detected, the function changes `readState` and `writeState` to true respectively to write enable signal

### `strobeDown` function

On strobe down read and write requests are executed. When on read state, value indexed by address bus is copied to data bus, and on write state - value from data bus is copied to array cell indexed by address bus.

## Data types

### Instance struct:

| Variable             | Description                                 |
| -------------------- | ------------------------------------------- |
| `uint8_t* data`      | pointer to an array with 65536 bytes        |
| `uint32_t size`      | length of data variable (65536)             |
| `uint8_t readState`  | used as bool to indicate data read request  |
| `uint8_t writeState` | used as bool to indicate data write request |

### interfaces

| ID   | Type        | Description            |
| ---- | ----------- | ---------------------- |
| 0    | `uint8_t*`  | 8 bit data bus         |
| 1    | `uint16_t*` | 16 bit address bus     |
| 2    | `uint8_t*`  | chip select (as bool)  |
| 3    | `uint8_t*`  | write enable (as bool) |

### create parameters - not implemented
