#include "Memory_Stage.h"

void MemStage(Pipeline_Reg *EX_MEM_Current, Pipeline_Reg *MEM_WB_Next, uint32_t *mem, CPU *cpu)
{
    *MEM_WB_Next = *EX_MEM_Current;

    if (EX_MEM_Current->instr->Type == 'S' || EX_MEM_Current->instr->Type == 'I')
    {

        switch (EX_MEM_Current->instr->Opcode)
        {
        case 0x1A:
            MEM_WB_Next->unsigned_int = LD_Instr(EX_MEM_Current, mem);
            // MEM_WB_Next->val = MEM_WB_Next->unsigned_int;
            break;

        case 0x1B:
            MEM_WB_Next->signed_half = LDH_Instr(EX_MEM_Current, mem);
            // MEM_WB_Next->val = (uint32_t)MEM_WB_Next->signed_half;
            break;

        case 0x1C:
            MEM_WB_Next->signed_byte = LDB_Instr(EX_MEM_Current, mem);
            // MEM_WB_Next->val = (uint32_t)MEM_WB_Next->signed_byte;
            break;

        case 0x1D:
            MEM_WB_Next->unsigned_half = LDUH_Instr(EX_MEM_Current, mem);
            // MEM_WB_Next->val = (uint32_t)MEM_WB_Next->unsigned_half;
            break;

        case 0x1E:
            MEM_WB_Next->unsigned_byte = LDUB_Instr(EX_MEM_Current, mem);
            // MEM_WB_Next->val = (uint32_t)MEM_WB_Next->unsigned_byte;
            break;

        case 0x1F:
            ST_Instr(EX_MEM_Current, mem, cpu);
            MEM_WB_Next->instr = NULL;
            break;

        case 0x20:
            STH_Instr(EX_MEM_Current, mem, cpu);
            MEM_WB_Next->instr = NULL;
            break;

        case 0x21:
            STB_Instr(EX_MEM_Current, mem, cpu);
            MEM_WB_Next->instr = NULL;
            break;

        default:
            break;
        }
    }
    else
    {
        return;
    }
}

uint32_t LD_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem)
{

    uint32_t v = readMemory(EX_MEM_Current->val, mem);
    return v;
}

int16_t LDH_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem)
{
    return (int16_t)(readMemory(EX_MEM_Current->val, mem));
}

int8_t LDB_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem)
{
    return (int8_t)(readMemory(EX_MEM_Current->val, mem));
}

uint16_t LDUH_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem)
{
    return (uint16_t)(readMemory(EX_MEM_Current->val, mem));
}

uint8_t LDUB_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem)
{
    return (uint8_t)(readMemory(EX_MEM_Current->val, mem));
}

void ST_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem, CPU *cpu)
{
    WriteMemory(EX_MEM_Current->val, mem, cpu->reg[EX_MEM_Current->instr->rs2]);
    return;
}

void STH_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem, CPU *cpu)
{
    WriteMemory(EX_MEM_Current->val, mem, (uint16_t)cpu->reg[EX_MEM_Current->instr->rs2]);
    return;
}

void STB_Instr(Pipeline_Reg *EX_MEM_Current, uint32_t *mem, CPU *cpu)
{
    WriteMemory(EX_MEM_Current->val, mem, (uint8_t)cpu->reg[EX_MEM_Current->instr->rs2]);
    return;
}

// void MemRegFree(Memory_Register *reg)
// {
//     free(reg);
// }
