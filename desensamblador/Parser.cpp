#include "Parser.hpp"



Parser::Parser(std::string program_path)
{
	// We open the file
	program_file.open(program_path);

	// We check if file exist
	if (!program_file.is_open()) throw std::runtime_error("Error: path incorrect or could not be opened '" + program_path + "'");
}

std::string Parser::get_current_line()
{
	return current_line;
}

bool Parser::has_more_lines()
{
	return program_file.peek() != EOF;
}

std::string Parser::advance()
{
	// Check for empty line
	if (!std::getline(program_file, current_line))
	{
		current_line = "";
		return current_line;
	}

	while (!current_line.empty() && (current_line.back() == '\r' || current_line.back() == '\n')) current_line.pop_back();

	// If line has number of characters != 16, fail.
	if (current_line.size() != 16) throw std::runtime_error("Error: expected 16 char in line, got " + std::to_string(current_line.size()) + " ('" + current_line + "')");

	if (is_all_binary(current_line)) return current_line;

	// if there are no lines left, we just return nothing
	current_line = "";
	return "";
}

InstructionType Parser::instruction_type()
{
	if (current_line[0] == '0') return InstructionType::A_INSTRUCTION;
	if (current_line[0] == '1') return InstructionType::C_INSTRUCTION;
	else return InstructionType::E_INSTRUCTION;
}

int Parser::symbol()
{
	int symbol = 0;

	try {symbol = std::stoi(current_line.substr(1), nullptr, 2);}
	catch (const std::out_of_range&) {throw std::runtime_error("Error: A instruction out of range '" + current_line + "'");}

	return symbol;
}

std::string Parser::dest()
{
	return current_line.substr(10, 3);
}

std::string Parser::comp()
{
	return current_line.substr(3, 7);
}

std::string Parser::jump()
{
	return current_line.substr(13, 3);
}



/*			HELPER FUNCTIONS			*/

void Parser::reset()
{
	program_file.clear();
	program_file.seekg(0);
}

std::string Parser::parse_args(int argc, char* argv[])
{
	std::string path;

	switch (argc)
	{
		case 1:
			path = DEFAULT_PROGRAM;
			break;

		case 2:
			path = argv[1];
			// We add the .hack if the user didn't specified it.
			if (path.length() < 4 || path.substr(path.length() - 4) != ".hack") path += ".hack";
			break;

		default:
			throw std::runtime_error("Error: more than one argument provided '" + std::string(argv[2]) + "'");
	}
	return path;
}

bool Parser::is_all_binary(const std::string& symbol)
{
	if (symbol.empty()) return false;

	for (char c : symbol)
		if (c != '0' && c != '1')
			return false;
	
	return true;
}