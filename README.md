# Assembler for Hack

## Integrantes
- Juan Pablo López
- Dios
- Loki (mi conéjo)

## Project Overview
This project is a C++ implementation of the Hack Assembler and Disassembler from the Nand2Tetris course. It translates Hack assembly language (`.asm`) into 16-bit machine code (`.hack`) and biceversa (`.hack` to `.asm`). It uses a two-pass architecture to handle predefined symbols, user-defined variables, and labels.

### Directory Layout
```text
Hack_Assembler/
├─ desensamblador/
│	├─ main.cpp
│	├─ Parser.hpp & .cpp
│	├─ Code.hpp & .cpp
│	└─ SymbolTable.hpp & .cpp
├─ ensamblador/
│	├─ main.cpp
│	├─ Parser.hpp & .cpp
│	├─ Code.hpp & .cpp
│	└─ SymbolTable.hpp & .cpp
├─ pruebas/
│	├─ desensamblador/
│	│	└─ *.hack
│	└─ ensamblador/
│		└─ *.asm
├─ DOCUMENTATION/
│	└─ INFORME.md
├─ .gitignore
├─ makefile
└─ README.md
```

## How to Build
To compile the assembler, run the following command in your terminal:

```bash
cd ensamblador
g++ -std=c++23 main.cpp Parser.cpp Code.cpp SymbolTable.cpp -o ensamblador
```

Alternatively you can compile the disassembler:

```bash
cd desensamblador
g++ -std=c++23 main.cpp Parser.cpp Code.cpp SymbolTable.cpp -o desensamblador
```

Optionally, if `make` or `makefile` are recognised in the system environments you can simply run:

```bash
make # builds the assembler and disassembler, runs them with their default paths, and cleans the .build folder.
make build
make clear

make en_build # to build the assembler
make de_build # to build the disassembler

make en_run # to run the assembler with the default program path (.asm)
make de_run # to build the disassembler with the default program path (.hack)

# to delete the .build folder use:
make clean
make clear
make cls # also clears the screeen right after
```

The first option will build, run and clear the version automatically, the second will only build and leave the .exe file ready for testing, the third will remove all builds made.

## How to Run
You can run the build with:

```bash
.build/ensamblador ./pruebas/ensamblador/Program.asm
.build/desensamblador ./pruebas/desensamblador/Program.hack
```

You can also skip the .asm (and the .hack) and the program will recognise the file, or you can run only the assembler without input path and it will use `Prog.asm` as a default.
