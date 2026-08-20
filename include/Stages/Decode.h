#include <stdio.h>
#include <unistd.h>
#include "CPU_Memory.h"
#include "CPU.h"

#ifndef DECODE_H
#define DECODE_H

Instruction *DecodeInstruction(uint32_t RawInstr, Pipeline_Reg *ID_EX_Next);

void DecodeOpcode(uint32_t RawInstr, Instruction *instr);

void DecodeRType(uint32_t RawInstr, Instruction *instr);

void DecodeIType(uint32_t RawInstr, Instruction *instr);

void DecodeSType(uint32_t RawInstr, Instruction *instr);

void DecodeBType(uint32_t RawInstr, Instruction *instr);

void DecodeJType(uint32_t RawInstr, Instruction *instr);

void DecodeTType(uint32_t RawInstr, Instruction *instr);

void checkType(Instruction *instr);

#endif