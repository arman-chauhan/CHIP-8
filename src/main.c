#include "external/include/raylib.h"
#include "include/chip8.h"
#include "include/common.h"

#define SCALE 20
#define SCALED_HEIGHT (SCALE * DISPLAY_HEIGHT)
#define SCALED_WIDTH (SCALE * DISPLAY_WIDTH)

const Color dark = {0xa8, 0x76, 0x2a, 0xff};
const Color light = {255, 220, 70, 255};
const KeyboardKey keys[16] = {
    KEY_X,      // 0
    KEY_ONE,    // 1
    KEY_TWO,    // 2
    KEY_THREE,  // 3
    KEY_Q,      // 4
    KEY_W,      // 5
    KEY_E,      // 6
    KEY_A,      // 7
    KEY_S,      // 8
    KEY_D,      // 9
    KEY_Z,      // A
    KEY_C,      // B
    KEY_FOUR,   // C
    KEY_R,      // D
    KEY_F,      // E
    KEY_V       // F
};

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to CHIP-8 rom>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Chip8State* state = InitChip8();
    LoadRom(state, argv[1]);
    InitWindow(SCALED_WIDTH, SCALED_HEIGHT, "CHIP-8 EMULATOR");
    printf("\n====================================================\n");

    const float timeStep = 1.0f / 60.0f;  // 60 Instructions per second
    float currentTime = GetTime();
    float accumulator = 0.0f;
    while (state->running) {
        if (WindowShouldClose()) state->running = 0;
        const float newTime = GetTime();
        const float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        for (uint8_t i = 0; i < 16; i++) {
            state->keys[i] = IsKeyDown(keys[i]) ? 1 : 0;
        }

        while (accumulator >= timeStep) {
            for (int i = 0; i < 8; i++) EmulateCycle(state);
            accumulator -= timeStep;  // Subtract fixed time step

            // Update timers
            if (state->DT > 0) { state->DT--; }
            if (state->ST > 0) { state->ST--; }
        }

        // Render the current frame
        BeginDrawing();
        ClearBackground(dark);

        for (int y = 0; y < 32; y++) {
            for (int x = 0; x < 64; x++) {
                const Color color = state->FB[y][x] ? light : dark;
                DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, color);
            }
        }
        EndDrawing();
    }

    // Cleanup
    free(state);
    CloseWindow();
    return EXIT_SUCCESS;
}
