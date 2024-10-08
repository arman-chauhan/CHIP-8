#include "include/chip8.h"

#include "include/instructions.h"

Chip8State* InitChip8(void) {
    Chip8State* state = malloc(sizeof(Chip8State));
    if (state == NULL) {
        perror("Error initializing CHIP-8");
        exit(EXIT_FAILURE);
    }

    const uint8_t font[80] = FONT_DATA;
    for (int i = 0; i < 80; i++) { state->memory[FONT_ADDR + i] = font[i]; }
    for (int i = 0; i < 16; i++) {
        state->V[i] = 0;
        state->keys[i] = 0;
    }
    state->PC = PROGRAM_START;
    state->running = 1;
    state->SP = 0;
    state->I = 0;
    state->DT = 0;
    state->ST = 0;
    return state;
}

void LoadRom(Chip8State* state, const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        perror("Error opening rom");
        free(state);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    const unsigned long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (fsize > MEMORY_SIZE - PROGRAM_START) {
        perror("Error rom to large");
        fclose(file);
        free(state);
        exit(EXIT_FAILURE);
    }

    if (fread(&state->memory[PROGRAM_START], sizeof(uint8_t), fsize, file) !=
        fsize) {
        perror("Error reading rom");
        fclose(file);
        free(state);
        exit(EXIT_FAILURE);
    };

    fclose(file);
}

void EmulateCycle(Chip8State* state) {
    Disassembler(state);
    printf("\n");

    // Implement instructions
}

void Disassembler(Chip8State* state) {
    const uint8_t* opCode = &state->memory[state->PC];
    const uint8_t firstnib = opCode[0] >> 4;
    const uint16_t nnn = (opCode[0] << 8 | opCode[1]) & 0x0FFF;
    const uint8_t x = opCode[0] & 0x0F;
    const uint8_t y = opCode[1] >> 4;
    const uint8_t kk = opCode[1];
    const uint8_t n = opCode[1] & 0x0F;

    printf("%#x %02x %02x ", state->PC, opCode[0], opCode[1]);
    switch (firstnib) {
        case 0x0: {
            switch (opCode[1]) {
                case 0xE0: printf("%s", "CLS"); break;
                case 0xEE: printf("%s", "RET"); break;
                default: printf("UNKNOWN 0: Possibly data"); break;
            }
        } break;
        case 0x1: printf("%-10s $%X", "JUMP_ABS", nnn); break;
        case 0x2: printf("%-10s $%X", "CALL", nnn); break;
        case 0x3: printf("%-10s V%01X,#$%02X", "SKIP.EQ", x, kk); break;
        case 0x4: printf("%-10s V%01X,#$%02X", "SKIP.NE", x, kk); break;
        case 0x5: printf("%-10s V%01X,V%01X", "SKIP.EQ", x, y); break;
        case 0x6: printf("%-10s V%01X,#$%02X", "LOAD", x, kk); break;
        case 0x7: printf("%-10s V%01X,#$%02X", "ADD", x, kk); break;
        case 0x8: {
            switch (n) {
                case 0x0: printf("%-10s V%01X,V%01X", "MOV", x, y); break;
                case 0x1: printf("%-10s V%01X,V%01X", "OR", x, y); break;
                case 0x2: printf("%-10s V%01X,V%01X", "AND", x, y); break;
                case 0x3: printf("%-10s V%01X,V%01X", "XOR", x, y); break;
                case 0x4: printf("%-10s V%01X,V%01X", "ADD.", x, y); break;
                case 0x5: printf("%-10s V%01X,V%01X", "SUB.", x, y); break;
                case 0x6: printf("%-10s V%01X,V%01X", "SHR.", x, y); break;
                case 0x7: printf("%-10s V%01X,V%01X", "SUBN.", x, y); break;
                case 0xe: printf("%-10s V%01X,V%01X", "SHL", x, y); break;
                default: printf("UNKNOWN 8: Possibly data"); break;
            }
        } break;
        case 0x9: printf("%-10s V%01X,V%01X", "SKI.NE", x, y); break;
        case 0xa: printf("%-10s I,$%X", "MVI", nnn); break;
        case 0xb: printf("%-10s $%X(V0)", "JUMP", nnn); break;
        case 0xc: printf("%-10s V%01X,#$%X", "RND", x, kk); break;
        case 0xd: printf("%-10s V%01X,V%01X,#$%02X", "DISPLAY", x, y, n); break;
        case 0xe: {
            switch (opCode[1]) {
                case 0x9e: printf("%-10s V%01X", "SKIPKEY.Y", x); break;
                case 0xa1: printf("%-10s V%01X", "SKIPKEY.N", x); break;
                default: printf("UNKNOWN E: Possibly data"); break;
            }
        } break;
        case 0xf: {
            switch (opCode[1]) {
                case 0x07: printf("%-10s V%01X,DT", "LOAD", x); break;
                case 0x0a: printf("%-10s V%01X,KEY", "LOAD_KEY", x); break;
                case 0x15: printf("%-10s DT,V%01X", "LOAD", x); break;
                case 0x18: printf("%-10s ST,V%01X", "MOV", x); break;
                case 0x1e: printf("%-10s I,V%01X", "ADD", x); break;
                case 0x29: printf("%-10s I,V%01X", "SPRITE", x); break;
                case 0x33: printf("%-10s (I),V%01X", "MOVBCD", x); break;
                case 0x55: printf("%-10s (I),V0-V%01X", "MOVR", x); break;
                case 0x65: printf("%-10s V0-V%01X,(I)", "MOVM", x); break;
                default: printf("UNKONWN F: Possibly data"); break;
            }
        } break;
        default: printf("UNKNOWN INSTRUCITON: Possibly data");
    }
}