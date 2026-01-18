#include "cpu_memory.h"

cpu_memory *allocateMem()
{
    cpu_memory mainMemory;
    cpu_memory *mainMemoryPointer;
    mainMemoryPointer = &mainMemory;

    int memSizeInput = 0;
    printf("Please enter the size of main memory in kb, eg for 64kb enter 64 or 32kb enter 32: ");

    scanf("%d", memSizeInput); 

    mainMemoryPointer->memSize = memSizeInput * 1024;
    mainMemoryPointer->ptr = (uint32_t *)malloc(mainMemoryPointer->memSize);

    if (mainMemoryPointer->memSize == 0)
    {
        printf("Failed to set memory size");
    }
    if (mainMemoryPointer->ptr == NULL)
    {
        printf("Failed to allocate memory");
    }

    return mainMemoryPointer;
}

void deallocateMem(cpu_memory *mainMemory)
{
    free(mainMemory->ptr);

    if (mainMemory->ptr == NULL)
    {
        printf("deallocated memory!");
    }
}

void mem_write(cpu_memory *mainMemory, uint32_t address, uint32_t value)
{
    mainMemory->ptr[address] = value;
}

uint32_t mem_read(uint32_t address, cpu_memory *mainMemory)
{
    uint32_t result = *(mainMemory->ptr + address);
    return result;
}