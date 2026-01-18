#include <stdio.h>
#include <stdint.h>
#include "CPU_Memory/cpu_memory.h"

uint32_t fetchInstruction(cpu_memory *MainMemory, uint32_t *pcValue);