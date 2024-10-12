# CHIP-8 Emulator
CHIP-8 is an interpreted language from the mid-1970s that was created for early 8-bit microcomputers. It is simple and depending on the version, contains about 35 opcodes. It was popularly used for graphing calculators and simple games.

## Prerequisites
- [Raylib](https://www.raylib.com/) for graphics and input
- Clang as compiler
- Make to run the Makefile

Note: This build configuration works for macOS out of the box. For other platforms, you need to replace `src/external/lib/libraylib.a` with the appropriate binary for your platform. Refer to the [Raylib installation guide](https://github.com/raysan5/raylib#build-and-installation) for more information. If it doesn't compile may you also need to link essential libraries for windowing and inputs, [here](https://github.com/arman-chauhan/CHIP-8/blob/d63b788710b25751b418e6d1ed470a16c7c5f458/Makefile#L17) in Makefile.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/arman-chauhan/CHIP-8.git
   cd CHIP-8
2. Build the binary:
   ```sh
   make
   ```
   The binary for the emulator will be created in the build directory along with object files.
3. Run the emulator:
   ```sh
   ./build/emu /path/to/rom
   ```
There are some playable ROMs in the roms directory.

Note: Not all CHIP-8 ROMs will work due to various quirks. Some ROMs may not work even if the frames per second and instructions per frame are different than intended.
