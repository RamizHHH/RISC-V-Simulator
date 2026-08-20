#include <stdio.h>
#include "CPU_Memory.h"
#include <stdint.h>
#include <unistd.h>
#include "WriteBack.h"

#ifndef PIPELINE_H
#define PIPELINE_H

void Pipeline(CPU *cpu, uint32_t *mem);

void printInstrStages(int Cycle, CPU *cpu, Pipeline_Reg **Registers);

Pipeline_Reg **InitalizePipelineReg();

void FreePipelineReg(Pipeline_Reg **Arr);

#endif