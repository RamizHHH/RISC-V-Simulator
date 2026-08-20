#include "Execute.h"

void ExecuteInstr(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next)
{
    ID_EX_Next->instr = ID_EX_Current->instr;
    ID_EX_Next->RawInstr = ID_EX_Current->RawInstr;
    ID_EX_Current->val = 0;

    if (ID_EX_Current->instr->Type == 'R')
    {
        isRType(cpu, ID_EX_Current, ID_EX_Next);
        return;
    }
    else if (ID_EX_Current->instr->Type == 'I')
    {
        isIType(cpu, ID_EX_Current, ID_EX_Next);
        return;
    }
    else if (ID_EX_Current->instr->Type == 'S')
    {
        isSType(cpu, ID_EX_Current, ID_EX_Next);
        return;
    }
    else if (ID_EX_Current->instr->Type == 'P')
    {
        isPType(cpu, ID_EX_Current);
        return;
    }
    else if (ID_EX_Current->instr->Type == 'B')
    {
        isBType(cpu, ID_EX_Current);
        return;
    }
    else if (ID_EX_Current->instr->Type == 'J')
    {

        isJType(cpu, ID_EX_Current, ID_EX_Next);
        return;
    }
    else
    {
        perror("Invalid Instruction");
        exit(1);
    }
}

void isRType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next)
{
    switch (ID_EX_Current->instr->Opcode)
    {
    case 0x01:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + cpu->reg[ID_EX_Current->instr->rs2];
        break;

    case 0x02:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] - cpu->reg[ID_EX_Current->instr->rs2];
        break;

    case 0x03:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] & cpu->reg[ID_EX_Current->instr->rs2];
        break;

    case 0x04:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] | cpu->reg[ID_EX_Current->instr->rs2];
        break;

    case 0x05:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] ^ cpu->reg[ID_EX_Current->instr->rs2];
        break;

    case 0x06:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] << (cpu->reg[ID_EX_Current->instr->rs2] & 31);
        break;

    case 0x07:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] >> (cpu->reg[ID_EX_Current->instr->rs2] & 31);
        break;

    case 0x08:

        ID_EX_Next->val = (int32_t)cpu->reg[ID_EX_Current->instr->rs1] >> (cpu->reg[ID_EX_Current->instr->rs2] & 31);
        break;

    case 0x09:
    {
        int16_t result = (int64_t)(int32_t)cpu->reg[ID_EX_Current->instr->rs2] * (int64_t)(int32_t)cpu->reg[ID_EX_Current->instr->rs2];
        ID_EX_Next->val = (uint32_t)result;
        break;
    }

    case 0x0A:

        if (cpu->reg[ID_EX_Current->instr->rs2] != 0)
        {
            ID_EX_Next->val = (uint32_t)((int32_t)cpu->reg[ID_EX_Current->instr->rs1] / (int32_t)cpu->reg[ID_EX_Current->instr->rs2]);
            break;
        }
        else
        {
            // ADD TRAP HERE
            perror("Error divide by zero");
            exit(1);
        }

    case 0x0B:

        if (cpu->reg[ID_EX_Current->instr->rs2] != 0)
        {
            ID_EX_Next->val = (uint32_t)((int32_t)cpu->reg[ID_EX_Current->instr->rs2] % (int32_t)cpu->reg[ID_EX_Current->instr->rs2]);
            break;
        }
        else
        {
            // ADD TRAP HERE
            perror("Error divide by zero");
            exit(1);
        }

        // case 0x0C:  DO WHEN FLAGS ARE IMPLEMENTED
        //     break;

    case 0x0D:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1];
        break;

    case 0x0E:

        ID_EX_Next->val = ~(cpu->reg[ID_EX_Current->instr->rs1]);
        break;

    case 0x0F:

        ID_EX_Next->val = 0 - (cpu->reg[ID_EX_Current->instr->rs1]);
        break;

    default:
        break;
    }
}

void isIType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next)
{

    switch (ID_EX_Current->instr->Opcode)
    {
    case 0x10:
        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x11:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] - ID_EX_Current->instr->imm;
        break;

    case 0x12:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] & ID_EX_Current->instr->imm;
        break;

    case 0x13:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] | ID_EX_Current->instr->imm;
        break;

    case 0x14:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] ^ ID_EX_Current->instr->imm;
        break;

    case 0x15:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] << (ID_EX_Current->instr->imm & 31);
        break;

    case 0x16:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] >> (ID_EX_Current->instr->imm & 31);
        break;

    case 0x17:

        ID_EX_Next->val = (int32_t)cpu->reg[ID_EX_Current->instr->rs1] >> (ID_EX_Current->instr->imm & 31);
        break;

    case 0x19:

        ID_EX_Next->val = ID_EX_Current->instr->imm;
        break;

    case 0x1A:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x1B:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x1C:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x1D:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x1E:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    default:
        break;
    }
}

void isSType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next)
{
    switch (ID_EX_Current->instr->Opcode)
    {

    case 0x1F:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x20:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    case 0x21:

        ID_EX_Next->val = cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm;
        break;

    default:
        break;
    }
}

void isBType(CPU *cpu, Pipeline_Reg *ID_EX_Current)
{
    if (ID_EX_Current->instr->Opcode == 0x22)
    {
        if (cpu->reg[ID_EX_Current->instr->rs1] == cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
    if (ID_EX_Current->instr->Opcode == 0x23)
    {
        if (cpu->reg[ID_EX_Current->instr->rs1] != cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
    if (ID_EX_Current->instr->Opcode == 0x24)
    {
        if ((int32_t)cpu->reg[ID_EX_Current->instr->rs1] <= (int32_t)cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
    if (ID_EX_Current->instr->Opcode == 0x25)
    {
        if ((int32_t)cpu->reg[ID_EX_Current->instr->rs1] >= (int32_t)cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
    if (ID_EX_Current->instr->Opcode == 0x26)
    {
        if (cpu->reg[ID_EX_Current->instr->rs1] <= cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
    if (ID_EX_Current->instr->Opcode == 0x27)
    {
        if (cpu->reg[ID_EX_Current->instr->rs1] >= cpu->reg[ID_EX_Current->instr->rs2])
        {
            cpu->pc += ID_EX_Current->instr->imm;
        }
    }
}

void isJType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next)
{
    if (ID_EX_Current->instr->Opcode == 0x28)
    {
        cpu->pc += ID_EX_Current->instr->imm;
    }
    else if (ID_EX_Current->instr->Opcode == 0x29)
    {

        ID_EX_Next->val = cpu->pc;
        cpu->pc += ID_EX_Current->instr->imm;
    }
    else if (ID_EX_Current->instr->Opcode == 0x2A)
    {
        ID_EX_Next->val = cpu->pc;
        cpu->pc = (cpu->reg[ID_EX_Current->instr->rs1] + ID_EX_Current->instr->imm) & ~1;
    }
}

void isPType(CPU *cpu, Pipeline_Reg *ID_EX_Current)
{
    if (ID_EX_Current->instr->Opcode == 0x32)
    {
        cpu->halted = 1;
        return;
    }
}

// void freeExRegister(Execute_Register *reg)
// {
//     free(reg);
//     return;
// }
