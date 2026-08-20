#include "Pipeline.h"

void Pipeline(CPU *cpu, uint32_t *mem)
{
    Pipeline_Reg **PipelineRegisters = InitalizePipelineReg();

    int cycle = 0;

    while (cpu->halted != 1)
    {
        memset(PipelineRegisters[IF_ID_Next], 0, sizeof(Pipeline_Reg));
        memset(PipelineRegisters[ID_EX_Next], 0, sizeof(Pipeline_Reg));
        memset(PipelineRegisters[EX_MEM_Next], 0, sizeof(Pipeline_Reg));
        memset(PipelineRegisters[MEM_WB_Next], 0, sizeof(Pipeline_Reg));

        PipelineRegisters[IF_ID_Next]->RawInstr = FetchInstruction(mem, cpu);

        if (PipelineRegisters[IF_ID_Current]->RawInstr != 0)
        {
            PipelineRegisters[ID_EX_Next]->instr = DecodeInstruction(PipelineRegisters[IF_ID_Current]->RawInstr, PipelineRegisters[ID_EX_Next]);
        }

        if (PipelineRegisters[ID_EX_Current]->instr != 0)
        {
            ExecuteInstr(cpu, PipelineRegisters[ID_EX_Current], PipelineRegisters[EX_MEM_Next]);
        }

        if (PipelineRegisters[EX_MEM_Current]->instr != 0)
        {
            MemStage(PipelineRegisters[EX_MEM_Current], PipelineRegisters[MEM_WB_Next], mem, cpu);
        }

        if (PipelineRegisters[MEM_WB_Current]->instr != 0)
        {
            WriteBack(PipelineRegisters[MEM_WB_Current], cpu);
        }

        printInstrStages(cycle, cpu, PipelineRegisters);

        *PipelineRegisters[IF_ID_Current] = *PipelineRegisters[IF_ID_Next];
        *PipelineRegisters[ID_EX_Current] = *PipelineRegisters[ID_EX_Next];
        *PipelineRegisters[EX_MEM_Current] = *PipelineRegisters[EX_MEM_Next];
        *PipelineRegisters[MEM_WB_Current] = *PipelineRegisters[MEM_WB_Next];

        cycle += 1;
    }

    FreePipelineReg(PipelineRegisters);
    return;
}

void printInstrStages(int Cycle, CPU *cpu, Pipeline_Reg **Registers)
{
    printf("====================================================\n"
           "\n");
    printf("Cycle: %d\n", Cycle);
    printf("PC: 0x%08x\n\n", cpu->pc);
    printf("Instr in Pipeline Per Stage\n");
    printf("Fetch: 0x%08x\n", Registers[IF_ID_Current]->RawInstr);
    if (Registers[ID_EX_Current]->RawInstr != 0)
        printf("Decode: 0x%08x\n", Registers[ID_EX_Current]->RawInstr);
    if (Registers[EX_MEM_Current]->RawInstr != 0)
        printf("Execute: 0x%08x\n", Registers[EX_MEM_Current]->RawInstr);
    if (Registers[MEM_WB_Current]->RawInstr != 0)
        printf("Memory/Writeback: 0x%08x\n", Registers[MEM_WB_Current]->RawInstr);
    printf("\n");
    printf("Registers\n----------------------------------------------------\n");
    printf("R1: %d R2: %d R3: %d R4: %d R5: %d\nR6: %d R7: %d R8: %d R9: %d R10: %d\n\n",
           cpu->reg[1], cpu->reg[2], cpu->reg[3], cpu->reg[4], cpu->reg[5], cpu->reg[6],
           cpu->reg[7], cpu->reg[8], cpu->reg[9], cpu->reg[10]);

    printf("====================================================\n"
           "\n");
}

Pipeline_Reg **InitalizePipelineReg()
{
    Pipeline_Reg **Arr = (Pipeline_Reg **)malloc(8 * sizeof(Pipeline_Reg *));
    for (int i = 0; i < 8; ++i)
    {
        Arr[i] = (Pipeline_Reg *)malloc(sizeof(Pipeline_Reg));
        memset(Arr[i], 0, sizeof(Pipeline_Reg));
    }
    return Arr;
}

void FreePipelineReg(Pipeline_Reg **Arr)
{
    for (int i = 0; i < 8; ++i)
    {
        free(Arr[i]);
        Arr[i] = NULL;
    }
    free(Arr);
}
