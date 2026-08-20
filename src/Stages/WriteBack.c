#include "WriteBack.h"

void WriteBack(Pipeline_Reg *MEM_WB_Current, CPU *cpu)
{
    if (MEM_WB_Current == NULL || MEM_WB_Current->instr == NULL)
    {
        return;
    }

    switch (MEM_WB_Current->instr->Opcode)
    {
    case 0x1A:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->unsigned_int;
        break;

    case 0x1B:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->signed_half;
        break;

    case 0x1C:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->signed_byte;
        break;

    case 0x1D:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->unsigned_half;
        break;

    case 0x1E:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->unsigned_byte;
        break;
    default:
        cpu->reg[MEM_WB_Current->instr->rd] = MEM_WB_Current->val;
        break;
    }

    cpu->reg[0] = 0;
    FreeInstr(MEM_WB_Current->instr);
}

void FreeInstr(Instruction *instr)
{
    free(instr);
}
