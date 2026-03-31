#ifndef EXEC_CONTROL
#define EXEC_CONTROL

#include "z80cpuMod.h"

enum Error halt(struct Instance* __restrict i, void** __restrict inf);
enum Error nop(struct Instance* __restrict i, void** __restrict inf);
enum Error daa(struct Instance* __restrict i, void** __restrict inf);
enum Error cpl(struct Instance* __restrict i, void** __restrict inf);
enum Error ccf(struct Instance* __restrict i, void** __restrict inf);
enum Error scf(struct Instance* __restrict i, void** __restrict inf);

uint8_t pairity(uint8_t a);
void increment16(uint8_t *H, uint8_t *L); 
void decrement16(uint8_t *H, uint8_t *L); 
uint8_t getAddCarries(uint8_t a, uint8_t b, uint8_t previousCarry); 
enum Error get_displacement(struct Instance *__restrict i, void **__restrict inf);

#endif
