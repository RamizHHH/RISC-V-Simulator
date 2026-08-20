#include "Decode.h"

Instruction *DecodeInstruction(uint32_t RawInstr, Pipeline_Reg *ID_EX_Next)
{
    Instruction *instr = malloc(sizeof(Instruction));

    DecodeOpcode(RawInstr, instr);
    ID_EX_Next->RawInstr = RawInstr;

    return instr;
}

void DecodeOpcode(uint32_t RawInstr, Instruction *instr)
{
    uint32_t RightShifted = RawInstr >> 26;
    uint32_t opcode = RightShifted & 0x3F;

    instr->Opcode = opcode;
    // printf("RawInstr = 0x%08X\n", RawInstr);
    // printf("Opcode = %u\n", opcode);
    checkType(instr);

    switch (instr->Type)
    {
    case 'R':
        DecodeRType(RawInstr, instr);
        break;

    case 'S':
        DecodeSType(RawInstr, instr);
        break;

    case 'I':
        DecodeIType(RawInstr, instr);
        break;

    case 'B':
        DecodeBType(RawInstr, instr);
        break;

    case 'J':
        DecodeJType(RawInstr, instr);
        break;

    default:
        break;
    }
}

void DecodeRType(uint32_t RawInstr, Instruction *instr)
{
    instr->rs1 = (RawInstr >> 16) & 0x1F;
    instr->rs2 = (RawInstr >> 11) & 0x1F;
    instr->rd = (RawInstr >> 21) & 0x1F;
    instr->imm = 0;
}

void DecodeIType(uint32_t RawInstr, Instruction *instr)
{
    instr->rs1 = (RawInstr >> 16) & 0x1F;
    instr->rs2 = 0;
    instr->rd = (RawInstr >> 21) & 0x1F;
    instr->imm = RawInstr & 0xFFFF;
}

void DecodeSType(uint32_t RawInstr, Instruction *instr)
{
    instr->rs1 = (RawInstr >> 16) & 0x1F;
    instr->rs2 = (RawInstr >> 21) & 0x1F;
    instr->rd = 0;
    instr->imm = RawInstr & 0xFFFF;
}

void DecodeBType(uint32_t RawInstr, Instruction *instr)
{
    instr->rs1 = (RawInstr >> 16) & 0x1F;
    instr->rs2 = (RawInstr >> 21) & 0x1F;
    instr->rd = 0;
    instr->imm = RawInstr & 0xFFFF;
}

void DecodeJType(uint32_t RawInstr, Instruction *instr)
{
    if (instr->Opcode == 0x28)
    {
        instr->rs1 = 0;
        instr->rs2 = 0;
        instr->rd = 0;
        instr->imm = (int16_t)RawInstr & 0xFFFF;
    }
    else if (instr->Opcode == 0x29)
    {
        instr->rs1 = 0;
        instr->rs2 = 0;
        instr->rd = (RawInstr >> 21) & 0x1F;
        instr->imm = (int16_t)RawInstr & 0xFFFF;
    }
    else if (instr->Opcode == 0x2A)
    {
        instr->rs1 = (RawInstr >> 16) & 0x1F;
        instr->rs2 = 0;
        instr->rd = (RawInstr >> 21) & 0x1F;
        instr->imm = (int16_t)RawInstr & 0xFFFF;
    }
}

void checkType(Instruction *instr)
{
    if (instr->Opcode >= 0x01 && instr->Opcode <= 0xF)
    {
        instr->Type = 'R';
    }
    else if (instr->Opcode >= 0x10 && instr->Opcode <= 0x1E)
    {
        instr->Type = 'I';
    }
    else if (instr->Opcode >= 0x1F && instr->Opcode <= 0x21)
    {
        instr->Type = 'S';
    }
    else if (instr->Opcode >= 0x22 && instr->Opcode <= 0x27)
    {
        instr->Type = 'B';
    }
    else if (instr->Opcode >= 0x28 && instr->Opcode <= 0x2A)
    {
        instr->Type = 'J';
    }
    else if (instr->Opcode >= 0x2B && instr->Opcode <= 0x33)
    {
        instr->Type = 'P';
    }
}