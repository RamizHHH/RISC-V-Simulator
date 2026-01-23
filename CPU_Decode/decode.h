#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t opcode;
    uint8_t Rd;
    uint8_t Funct3;
    uint8_t Rs1;
    uint8_t Rs2;
    uint8_t Funct7;

} RType;

typedef struct
{
    uint8_t opcode;
    uint8_t Rd;
    uint8_t Funct3;
    uint8_t Rs1;
    uint16_t Imm0_11;

} IType;

typedef struct
{
    uint8_t opcode;
    uint8_t Imm4_0;
    uint8_t Funct3;
    uint8_t Rs1;
    uint8_t Rs2;
    uint8_t Imm5_11;

} SType;

typedef struct
{

    uint8_t opcode;
    uint8_t Imm11_4_1;
    uint8_t Funct3;
    uint8_t Rs1;
    uint8_t Rs2;
    uint8_t Imm10_5_12;

} BType;

typedef struct
{

    uint8_t opcode;
    uint8_t Rd;
    uint32_t Imm12_31;

} UType;

typedef struct
{

    uint8_t opcode;
    uint8_t Rd;
    uint32_t Imm12_31;

} UType;