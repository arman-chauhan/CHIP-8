#ifndef CHIP8_H
#define CHIP8_H

#include "common.h"

// CHIP-8 Constants
#define MEMORY_SIZE 4096
#define REGISTER_NUM 16
#define STACK_SIZE 16
#define PROGRAM_START 0x200
#define KEYS 16
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64
#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)

typedef struct Chip8State {
    uint64_t memory[MEMORY_SIZE];  // 4kb total memory
    uint8_t V[REGISTER_NUM];       // General puporse registers (except VF)
    uint16_t I;                    // Index register
    uint16_t PC;                   // Program Counter
    uint16_t stack[STACK_SIZE];    // Stack (16 levels deep)
    uint8_t SP;  // Stack Pointer (tracks the top of the stack)
    uint8_t DT;  // Delay timer (counts down to zero)
    uint8_t ST;  // Sound timer (counts down to zero, makes sound when non-zero)

    uint8_t FB[DISPLAY_SIZE];  // Frame Buffer
    uint8_t keys[KEYS];        // Key state (16 keys)

    uint16_t romsize;  // Size of the rom
    uint8_t draw;      // Flag to incidcate need to redraw
    uint8_t running;   // Emulator running state
} Chip8State;

Chip8State* InitChip8(void);  // Initialize CHIP-8 state struct
void LoadRom(Chip8State* state, const char* path);  // Load game rom into memory

#endif