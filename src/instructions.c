#include "include/instructions.h"

#include "include/chip8.h"

void CLS(Chip8State *state) {
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) { state->FB[i][j] = 0; }
    }
    state->PC += 2;
}
void RET(Chip8State *state) {
    state->SP--;
    state->PC = state->stack[state->SP];
}
void CALL(Chip8State *state, uint8_t *opCode) {
    const uint16_t nnn = GET_NNN(opCode);
    if (state->SP >= 16) {
        perror("Error: STACK OVERFLOW");
        state->running = 0;
    }
    // Push (PC + 2) to stack, since PC points to current CALL
    state->stack[state->SP] = state->PC + 2;
    state->SP++;
    state->PC = nnn;
}
void JUMP_ABS(Chip8State *state, uint8_t *opCode) {
    const uint16_t nnn = GET_NNN(opCode);
    state->PC = nnn;
}
void JUMP_REL(Chip8State *state, uint8_t *opCode) {
    const uint16_t nnn = GET_NNN(opCode);
    state->PC = nnn + state->V[0];
}

void SKIP_EQ(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t kk = GET_KK(opCode);
    if (state->V[x] == kk) state->PC += 2;
    state->PC += 2;
}
void SKIP_NEQ(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t kk = GET_KK(opCode);
    if (state->V[x] != kk) state->PC += 2;
    state->PC += 2;
}
void SKIP_EQ_REG(Chip8State *state, uint8_t *opCdoe) {
    const uint8_t x = opCdoe[0] & 0x0f;
    const uint8_t y = opCdoe[1] >> 4;
    if (state->V[x] == state->V[y]) state->PC += 2;
    state->PC += 2;
}
void SKIP_NEQ_REG(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    if (state->V[x] != state->V[y]) state->PC += 2;
    state->PC += 2;
}

void LOAD(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t kk = GET_KK(opCode);
    state->V[x] = kk;
    state->PC += 2;
}
void MVI(Chip8State *state, uint8_t *opCode) {
    const uint16_t nnn = GET_NNN(opCode);
    state->I = nnn;
    state->PC += 2;
}
void MOV(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    state->V[x] = state->V[y];
    state->PC += 2;
}
void MOVD(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    state->DT = state->V[x];
    state->PC += 2;
}
void MOVS(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    state->ST = state->V[x];
    state->PC += 2;
}
void MOVR(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    for (int i = 0; i <= x; i++) { state->memory[state->I + i] = state->V[i]; }
    state->I += (x + 1);
    state->PC += 2;
}
void MOVM(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    for (int i = 0; i <= x; i++) { state->V[i] = state->memory[state->I + i]; }
    state->I += (x + 1);
    state->PC += 2;
}
void LOADD(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    state->V[x] = state->DT;
    state->PC += 2;
}
void MOVBCD(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = state->V[GET_X(opCode)];
    state->memory[state->I] = x / 100;
    state->memory[state->I + 1] = x / 10 % 10;
    state->memory[state->I + 2] = x % 10;
    state->PC += 2;
};

void ADI(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    state->I += state->V[x];
    state->PC += 2;
}
void ADD(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t kk = GET_KK(opCode);
    state->V[x] = state->V[x] + kk;
    state->PC += 2;
}
void AND(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    state->V[x] &= state->V[y];
    state->PC += 2;
    state->V[0xf] = 0;
}
void OR(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    state->V[x] |= state->V[y];
    state->PC += 2;
    state->V[0xf] = 0;
}
void XOR(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    state->V[x] ^= state->V[y];
    state->PC += 2;
    state->V[0xf] = 0;
}
void SHR(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t LSB = state->V[x] & 0x01;  // List Significant Bit
    state->V[x] = state->V[x] >> 1;
    state->V[0xf] = LSB;
    state->PC += 2;
}
void SHL(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t MSB = state->V[x] >> 7;  // Most Significant Bit
    state->V[x] = state->V[x] << 1;
    state->V[0xf] = MSB;
    state->PC += 2;
}
void RAND(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t kk = GET_KK(opCode);
    state->V[x] = rand() % 255 + kk;
    state->PC += 2;
}
void ADD_REG(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    const uint16_t res = state->V[x] + state->V[y];
    state->V[x] = res & 0x00ff;
    state->V[0xf] = res > 0xff;
    state->PC += 2;
}
void SUB_REG(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    const uint8_t res = state->V[x] - state->V[y];
    const uint8_t borrow = state->V[x] >= state->V[y];
    state->V[x] = res;
    state->V[0xf] = borrow;
    state->PC += 2;
}
void SUBN_REG(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    const uint8_t y = GET_Y(opCode);
    state->V[x] = state->V[y] - state->V[x];
    state->V[0xf] = state->V[y] > state->V[x];
    state->PC += 2;
}

void DRAW(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = state->V[GET_X(opCode)] % DISPLAY_WIDTH;
    const uint8_t y = state->V[GET_Y(opCode)] % DISPLAY_HEIGHT;
    const uint8_t n = GET_KK(opCode) & 0x0F;

    state->V[0xF] = 0;
    for (uint8_t row = 0; row < n; row++) {
        const uint8_t pixelRow = state->memory[state->I + row];
        uint8_t col = x;

        for (int8_t bit = 7; bit >= 0; bit--) {
            const uint8_t pixel = pixelRow & (1 << bit);
            // Check for collision
            if (pixel && state->FB[y + row][col]) state->V[0xF] = 1;

            // XOR the framebuffer with the pixel value
            state->FB[y + row][col] ^= pixel;
            if (++col >= DISPLAY_WIDTH) break;
        }
        if (y + row >= DISPLAY_HEIGHT) break;
    }
    state->PC += 2;
}
void SPRITE(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    state->I = FONT_ADDR + state->V[x] * 5;
    state->PC += 2;
}
void KEY_PRS(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    if (state->keys[state->V[x]]) state->PC += 2;
    state->PC += 2;
}
void KEY_NPRS(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    if (!state->keys[state->V[x]]) state->PC += 2;
    state->PC += 2;
}
void KEY_WAIT(Chip8State *state, uint8_t *opCode) {
    const uint8_t x = GET_X(opCode);
    for (int i = 0; i < 16; i++) {
        if (state->keys[i]) {
            state->V[x] = i;
            state->PC += 2;
            return;
        }
    }
}
