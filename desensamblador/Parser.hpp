#ifndef HACK_DISASSEMBLER_PARSER
#define HACK_DISASSEMBLER_PARSER

#include <fstream>
#include <string>

// For the different types of instructions there are.
enum class InstructionType {
    A_INSTRUCTION,
    C_INSTRUCTION,
	// No need for an L type this time arround.
    // Error instruction is also not needed, as instructions are WAY simpler now.
};

class Parser
{
	std::ifstream program_file;
	std::string current_line;

	static inline const std::string DEFAULT_PROGRAM = ".\\pruebas\\desensamblador\\Prueba3.hack";
public:
	Parser(std::string program_path);

	std::string get_current_line();

	// Checks if there is more work to do
	bool has_more_lines();
	std::string advance();

	// Returns instruction type
	InstructionType instruction_type();

	// For A (or Label too)
	int value_A();

	// For C

	std::string dest(); // A, D, M or any combination.
	std::string comp(); // I like to call it Operation, it's more intuitive
	std::string jump(); // self explanatory for those who know hack



	/*	HELPER FUNCTIONS	*/

	void reset(); // For second pass

	static std::string parse_args(int argc, char* argv[]);

	static bool is_all_binary(const std::string& symbol);
};

#endif