#ifndef HACK_ASSEMBLER_CODE
#define HACK_ASSEMBLER_CODE

#include <string>

struct Code
{
	static std::string dest(std::string);
	static std::string comp(std::string);
	static std::string jump(std::string);
};

#endif