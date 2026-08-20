#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "Decode.h"

#ifndef EXECUTE_H
#define EXECUTE_H

typedef struct
{
    uint32_t value;

} Execute_Register;

void ExecuteInstr(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next);

void isRType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next);

void isIType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next);

void isSType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next);

void isBType(CPU *cpu, Pipeline_Reg *ID_EX_Current);

void isJType(CPU *cpu, Pipeline_Reg *ID_EX_Current, Pipeline_Reg *ID_EX_Next);

void isPType(CPU *cpu, Pipeline_Reg *ID_EX_Current);

// void freeExRegister(Execute_Register *reg);

#endif