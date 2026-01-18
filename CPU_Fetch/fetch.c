#include "fetch.h"

uint32_t fetchInstruction(cpu_memory *MainMemory, uint32_t *pcValue)
{
    uint32_t pc = *pcValue;
    uint32_t instruction = mem_read(pc, &MainMemory);
    *pcValue++;
    return instruction;
}