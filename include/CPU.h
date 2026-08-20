#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef CPU_H
#define CPU_H

typedef enum
{
    IF_ID_Current = 0,
    IF_ID_Next = 1,
    ID_EX_Current = 2,
    ID_EX_Next = 3,
    EX_MEM_Current = 4,
    EX_MEM_Next = 5,
    MEM_WB_Current = 6,
    MEM_WB_Next = 7

} Pipeline_Reg_Codes;

typedef struct
{
    int halted;
    uint32_t reg[32];
    uint32_t pc;

} CPU;

typedef struct
{
    char Type;
    uint8_t Opcode;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t rd;
    int16_t imm;
    uint32_t OgInstr;

} Instruction;

typedef struct
{
    Instruction *instr;
    uint32_t val;
    uint32_t RawInstr;

    uint32_t unsigned_int;
    int16_t signed_half;
    int8_t signed_byte;
    uint16_t unsigned_half;
    uint8_t unsigned_byte;

} Pipeline_Reg;

CPU *initalizeCPU();

void freeCPU(CPU *cpu);

#endif