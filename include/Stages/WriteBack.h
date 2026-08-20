#include <stdio.h>
#include <unistd.h>
#include "Memory_Stage.h"
#include "Fetch.h"

#ifndef WRITEBACK_H
#define WRITEBACK_H

void WriteBack(Pipeline_Reg *MEM_WB_Current, CPU *cpu);

void FreeInstr(Instruction *instr);

#endif