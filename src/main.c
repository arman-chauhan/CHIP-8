#include <stdio.h>
#include <stdlib.h>

#include "external/include/raylib.h"

int main() {
    InitWindow(800, 450, "CHIP-8 EMULATOR");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20,
                 LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}