#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int *ptr;
    size_t memSize;

} cpu_memory;

cpu_memory *allocateMem();
void deallocateMem(cpu_memory *mainMemory);
void mem_write(cpu_memory *mainMemory, uint32_t address, uint32_t value);
uint32_t mem_read(uint32_t address, cpu_memory *mainMemory);