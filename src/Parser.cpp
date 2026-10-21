#include "Parser.hpp"

#include <iostream>
#include <string>

Parser::Parser(std::string program_path)
{
	// We open the file
	program_file.open(program_path);

	// We check if file exist
	if (!program_file.is_open())
	{
		throw std::runtime_error("Error: path incorrect or could not be opened: " + program_path);
	}
}

std::string Parser::parse_args(int argc, char* argv[])
{
	std::string path;

	switch (argc)
	{
		case 1:
			path = ".\\programs\\Prog.asm";
			break;

		case 2:
			path = argv[1];
			// We add the .asm if the user didn't specified it.
			if (path.length() < 4 || path.substr(path.length() - 4) != ".asm") path += ".asm";
			break;

		default:
			throw std::runtime_error("Error: more than one argument provided: " + *argv[2]);
	}
	return path;
}