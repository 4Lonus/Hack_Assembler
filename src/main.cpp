#include "Parser.hpp"

#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		/*			Parsing			*/

		// We parse the path to the file
		auto program_path = Parser::parse_args(argc, argv);

		// We open the program
		Parser p(program_path);

		// <--- from here all is testing
		std::string current_line;

		while (std::getline(p.program_file, current_line)) std::cout << current_line << std::endl;

		p.program_file.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}