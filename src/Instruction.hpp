#ifndef HACK_ASSEMBLER_INSTRUCTION
#define HACK_ASSEMBLER_INSTRUCTION

#include <string>

enum class InstructionType {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION,
    E_INSTRUCTION // Error instruction, also may stand for Empty, idk.
};

struct Instruction
{
	InstructionType type;
	std::string raw_code_line;

	// For A (or Label too)
	std::string symbol;

	// For C
	std::string dest; // A, D, M or any combination.
	std::string comp; // I like to call it Operation, it's more intuitive
	std::string jump; // self explanatory for those who know hack
};

#endif