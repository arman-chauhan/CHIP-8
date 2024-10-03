#include "external/include/raylib.h"
#include "include/chip8.h"
#include "include/common.h"

#define SCALE 10
#define SCALED_HEIGHT (SCALE * DISPLAY_HEIGHT)
#define SCALED_WIDTH (SCALE * DISPLAY_WIDTH)

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to CHIP-8 rom>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Chip8State* state = InitChip8();
    LoadRom(state, argv[1]);
    InitWindow(SCALED_WIDTH, SCALED_HEIGHT, "CHIP-8 EMULATOR");

    while (state->running) {
        if (WindowShouldClose()) state->running = 0;

        // Draw screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        // emulate and render cycles
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
