#ifndef HACK_ASSEMBLER_PARSER
#define HACK_ASSEMBLER_PARSER

#include <fstream>

class Parser
{
public:
	std::ifstream program_file;

	Parser(std::string program_path);

	static std::string parse_args(int argc, char* argv[]);
};

#endif