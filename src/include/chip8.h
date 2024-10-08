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
#define FONT_ADDR 0x050
#define FONT_DATA                                 \
    {                                             \
        0xF0, 0x90, 0x90, 0x90, 0xF0,     /* 0 */ \
            0x20, 0x60, 0x20, 0x20, 0x70, /* 1 */ \
            0xF0, 0x10, 0xF0, 0x80, 0xF0, /* 2 */ \
            0xF0, 0x10, 0xF0, 0x10, 0xF0, /* 3 */ \
            0x90, 0x90, 0xF0, 0x10, 0x10, /* 4 */ \
            0xF0, 0x80, 0xF0, 0x10, 0xF0, /* 5 */ \
            0xF0, 0x80, 0xF0, 0x90, 0xF0, /* 6 */ \
            0xF0, 0x10, 0x20, 0x40, 0x40, /* 7 */ \
            0xF0, 0x90, 0xF0, 0x90, 0xF0, /* 8 */ \
            0xF0, 0x90, 0xF0, 0x10, 0xF0, /* 9 */ \
            0xF0, 0x90, 0xF0, 0x90, 0x90, /* A */ \
            0xE0, 0x90, 0xE0, 0x90, 0xE0, /* B */ \
            0xF0, 0x80, 0x80, 0x80, 0xF0, /* C */ \
            0xE0, 0x90, 0x90, 0x90, 0xE0, /* D */ \
            0xF0, 0x80, 0xF0, 0x80, 0xF0, /* E */ \
            0xF0, 0x80, 0xF0, 0x80, 0x80  /* F */ \
    }

typedef struct Chip8State {
    uint8_t memory[MEMORY_SIZE];  // 4kb total memory
    uint8_t V[REGISTER_NUM];      // General puporse registers (except VF)
    uint16_t I;                   // Index register
    uint16_t PC;                  // Program Counter
    uint16_t stack[STACK_SIZE];   // Stack (16 levels deep)
    uint8_t SP;                   // Stack Pointer (tracks the top of the stack)
    uint8_t DT;                   // Delay timer (counts down to zero)
    uint8_t ST;  // Sound timer (counts down to zero, makes sound when non-zero)

    uint8_t FB[DISPLAY_HEIGHT][DISPLAY_WIDTH];  // Frame Buffer
    uint16_t keys[16];                          // Key state (16 keys)
    uint8_t running;                            // Emulator running state
} Chip8State;

// Chip-8 fetch macros
#define GET_X(ptr) (*(ptr) & 0x0f)      // opCode[0] & 0x0f
#define GET_Y(ptr) (*(ptr + 1) >> 4)    // opCode[1] >> 4
#define GET_KK(ptr) (*(ptr + 1))        // opCode[1]
#define GET_N(ptr) (*(ptr + 1) & 0x0f)  // opCode[1] & 0x0f
                                        // (opCode[0] << 8 | opCode[1]) & 0x0fff
#define GET_NNN(ptr) ((*(ptr) << 8 | *(ptr + 1)) & 0x0fff)

// Chip-8 functions
Chip8State* InitChip8(void);
void LoadRom(Chip8State* state, const char* path);
void EmulateCycle(Chip8State* state);  // Emulate a single cycle
void Disassembler(Chip8State* state);  // Disassemble a single instruction

#endif