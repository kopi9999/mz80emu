# test module

## Function

This module is a sample that demonstrates principle of a module. 

### `strobeUp` function

On strobe up value stored in `instance->value` is printed to standard output, and `interfaces[0]` is set to random value using `rand()` function.

### `strobeDown` function

On strobe down value of `instance->value` is set to `interfaces[0]`

## Data types

### Instance structure

```
struct Instance() {
	uint8_t value; 
	char* character; //unused
};
```

### interfaces

#### `interface[0]` - `uint8_t*`

### create parameters

`parameters[0]`: sets initial `value` value. Where `NULL`, `value = 0`
`parameters[1]`: sets initial `*character` value. Where `NULL`, `*character = 0`