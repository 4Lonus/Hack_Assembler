#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string program_path = ".\\programs\\Prog.asm";

	// We open the file
	std::ifstream program_file(program_path);

	// We check if file exist
	if (!program_file.is_open())
	{
		std::cerr << "Error: path incorrect or could not be opened: " << program_path << std::endl;
		return 1; 
	}

	std::string current_line;

	while (std::getline(program_file, current_line))
	{
		std::cout << current_line << std::endl;
	}

	program_file.close();

	return 0;
}