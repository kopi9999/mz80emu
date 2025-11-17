#ifndef DECODE
#define DECODE

#include "z80cpuMod.h"

enum Instruction decodeInstruction(struct Instance* __restrict i);
enum Instruction decodeInstruction_CB (struct Instance* __restrict i);
enum Instruction decodeInstruction_ED (struct Instance* __restrict i);

#endif
