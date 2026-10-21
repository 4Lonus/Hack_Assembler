#ifndef HACK_ASSEMBLER_PARSER
#define HACK_ASSEMBLER_PARSER

#include <fstream>
#include <string>

// For the different types of instructions there are.
enum class InstructionType {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION,
    E_INSTRUCTION // Error instruction, also may stand for Empty, idk.
};

class Parser
{
	std::ifstream program_file;
	std::string current_line;

	static inline const std::string DEFAULT_PROGRAM = ".\\programs\\Prog.asm";

	static bool is_all_digits(const std::string& symbol);
	static bool is_valid_char(const std::string& symbol);
public:
	Parser(std::string program_path);

	std::string get_current_line();

	// Checks if there is more work to do
	bool has_more_lines();
	std::string advance();

	// Returns instruction type
	InstructionType instruction_type();

	// For A (or Label too)
	std::string symbol();

	// For C

	std::string dest(); // A, D, M or any combination.
	std::string comp(); // I like to call it Operation, it's more intuitive
	std::string jump(); // self explanatory for those who know hack


	/*	HELPER FUNCTIONS	*/

	static std::string parse_args(int argc, char* argv[]);
};

#endif