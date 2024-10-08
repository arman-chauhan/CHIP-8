#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"
#include "common.h"

void CLS(Chip8State *state);  // 00E0
void RET(Chip8State *state);  // 00EE

void JUMP_ABS(Chip8State *state, uint8_t *opCode);     // 1nnn
void CALL(Chip8State *state, uint8_t *opCode);         // 2nnn
void SKIP_EQ(Chip8State *state, uint8_t *opCode);      // 3xkk
void SKIP_NEQ(Chip8State *state, uint8_t *opCode);     // 4xkk
void SKIP_EQ_REG(Chip8State *state, uint8_t *opCdoe);  // 5xy0
void LOAD(Chip8State *state, uint8_t *opCode);         // 6xkk
void ADD(Chip8State *state, uint8_t *opCode);          // 7xkk

void MOV(Chip8State *state, uint8_t *opCode);       // 8xy0
void OR(Chip8State *state, uint8_t *opCode);        // 8xy1
void AND(Chip8State *state, uint8_t *opCode);       // 8xy2
void XOR(Chip8State *state, uint8_t *opCode);       // 8xy3
void ADD_REG(Chip8State *state, uint8_t *opCode);   // 8xy4
void SUB_REG(Chip8State *state, uint8_t *opCode);   // 8xy5
void SHR(Chip8State *state, uint8_t *opCode);       // 8xy6
void SUBN_REG(Chip8State *state, uint8_t *opCode);  // 8xy7
void SHL(Chip8State *state, uint8_t *opCode);       // 8xyE

void SKIP_NEQ_REG(Chip8State *state, uint8_t *opCode);  // 9xy0
void MVI(Chip8State *state, uint8_t *opCode);           // Annn
void JUMP_REL(Chip8State *state, uint8_t *opCode);      // Bnnn
void RAND(Chip8State *state, uint8_t *opCode);          // Cxkk
void DRAW(Chip8State *state, uint8_t *opCode);          // Dxyn
void KEY_PRS(Chip8State *state, uint8_t *opCode);       // Ex9E
void KEY_NPRS(Chip8State *state, uint8_t *opCode);      // ExA1

void LOADD(Chip8State *state, uint8_t *opCode);     // Fx07
void KEY_WAIT(Chip8State *state, uint8_t *opCode);  // Fx0A
void MOVD(Chip8State *state, uint8_t *opCode);      // Fx15
void MOVS(Chip8State *state, uint8_t *opCode);      // Fx18
void ADI(Chip8State *state, uint8_t *opCode);       // Fx1E
void SPRITE(Chip8State *state, uint8_t *opCode);    // Fx29
void MOVBCD(Chip8State *state, uint8_t *opCode);    // Fx33
void MOVR(Chip8State *state, uint8_t *opCode);      // Fx55
void MOVM(Chip8State *state, uint8_t *opCode);      // Fx65

#endif