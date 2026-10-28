# Assembler for Hack

## Integrantes
- Juan Pablo López
- Dios
- Loki (mi conéjo)

## Project Overview
This project is a C++ implementation of the Hack Assembler from the Nand2Tetris course. It translates Hack assembly language (`.asm`) into 16-bit machine code (`.hack`). It uses a two-pass architecture to handle predefined symbols, user-defined variables, and labels.

### Directory Layout
**`hack_Assembler/`**:
├─ **`ensamblador/`**:
│  ├─ **`main.cpp`**: The entry point to the program. Two-pass process (First pass for labels, Second pass for translation) and handles file I/O.
│  ├─ **`Parser.hpp` / `Parser.cpp`**: Handles file reading, string manipulation, stripping comments/whitespace, and extracting instruction components (`symbol`, `dest`, `comp`, `jump`).
│  ├─ **`Code.hpp` / `Code.cpp`**: Contains lookup tables (`std::unordered_map`) which translate `dest`, `comp`, and `jump`codes into their binary representations.
│  └─ **`SymbolTable.hpp` / `SymbolTable.cpp`**: Manages the mapping of symbols (labels and variables) to memory addresses. Pre-loaded with Hack predefined symbols.
│
├─ **`desensamblador/`**:
│
├─ **`pruebas/`**: Contains test files and generated outputs.
│  ├─Includes various `.asm` test files (e.g., `Prog.asm`, `final.asm`, `valid_invalid_instructions.asm`).
│  └─Generated `.hack` output files will appear here.
│
├─ **`makefile`**: Automation script.
└─ **`.gitignore`**: tells GitHub to ignore `.build/`.

## How to Build
To compile the assembler, run the following command in your terminal:

```bash
g++ -std=c++23 main.cpp Parser.cpp Code.cpp SymbolTable.cpp -o assembler
```

Optionally, if `make` or `makefile` are recognised in the system environments you can run:

```bash
make
make build
make clear
```

The first option will build, run and clear the version automatically, the second will only build and leave the .exe file ready for testing, the third will remove all builds made.

## How to Run
You can run the build with:

```bash
.build/assembler ./programs/Program.asm
```

you can also skip the .asm and the program will recognise the file, or you can run only the assembler without input path and it will use `Prog.asm` as a default.
