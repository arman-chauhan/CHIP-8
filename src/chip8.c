#include "include/chip8.h"

Chip8State* InitChip8(void) {
    Chip8State* state = malloc(sizeof(Chip8State));
    if (state == NULL) {
        perror("Error initializing CHIP-8");
        exit(EXIT_FAILURE);
    }

    state->PC = PROGRAM_START;
    state->running = 1;
    state->draw = 1;
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

    state->romsize = fsize;

    if (fread(&state->memory[PROGRAM_START], sizeof(uint8_t), fsize, file) !=
        fsize) {
        perror("Error reading rom");
        fclose(file);
        free(state);
        exit(EXIT_FAILURE);
    };

    fclose(file);
}