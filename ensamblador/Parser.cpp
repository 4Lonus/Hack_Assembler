#include "Parser.hpp"

#include <algorithm>

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
	while (std::getline(program_file, current_line))
	{
		// We first must remove all white spaces and tabs from the line (start and end)
		current_line.erase(std::remove(current_line.begin(), current_line.end(), ' '), current_line.end()); // we delete all spaces
		current_line.erase(std::remove(current_line.begin(), current_line.end(), '\t'), current_line.end()); // we delete all tabs
		current_line.erase(std::remove(current_line.begin(), current_line.end(), '\r'), current_line.end()); // we delete all return

		// if what's remaning is empty or it's only a comment, then we skip
		if (current_line.empty() || current_line[0] == '/') continue;

		// we look for a inline comments
		size_t comment_pos = current_line.find('/');

		// if we find them, we remove them.
		if (comment_pos != std::string::npos) current_line = current_line.substr(0, comment_pos);

		if (current_line.empty()) continue;

		return current_line;
	}

	// if there are no lines left, we just return nothing
	current_line = "";
	return current_line;
}

InstructionType Parser::instruction_type()
{
	if (current_line.empty()) return InstructionType::E_INSTRUCTION;
	else if (current_line[0] == '@') // We check if it's A
	{
		// If it's only a @, it's an error
		if (current_line.length() == 1) return InstructionType::E_INSTRUCTION;

		std::string symbol = current_line.substr(1);

		// we check if the post-@ content is purely numbers or valid chacracters.
		if (is_all_digits(symbol) || is_valid_char(symbol)) return InstructionType::A_INSTRUCTION;
		else return InstructionType::E_INSTRUCTION;
	}

	// We check if it's L
	else if (current_line[0] == '(')
	{
		if (current_line.length() < 3 || current_line.back() != ')') return InstructionType::E_INSTRUCTION;

		std::string symbol = current_line.substr(1, current_line.length() - 2);

		if (is_valid_char(symbol)) return InstructionType::L_INSTRUCTION;
		else return InstructionType::E_INSTRUCTION;
	}
	else return InstructionType::C_INSTRUCTION;
}

std::string Parser::symbol()
{
	if (current_line.empty() || current_line.length() <= 1) return "";
	// check for A
	else if (current_line[0] == '@')
	{
		std::string symbol = current_line.substr(1);

		// must be an integer or aphanimeric + "_" + "." + "$" + ":"
		if (!is_all_digits(symbol) && !is_valid_char(symbol)) return "";
		return symbol;
	}
	// check for L
	else if (current_line[0] == '(')
	{
		// we must cut the first and last char
		std::string symbol = current_line.substr(1, current_line.length() - 2);

		// must be alfanumeric + "_" + "." + "$" + ":"
		if (!is_valid_char(symbol)) return "";
		return symbol;
	}
	else return "";
}

std::string Parser::dest()
{
	if (current_line.empty()) return "";
	
	// destintation requires an equal symbol
	size_t eq_pos = current_line.find('=');
	if (eq_pos == std::string::npos) return "";

	// we get the isolated destination
	std::string dest = current_line.substr(0, eq_pos);

	return dest;
}

std::string Parser::comp()
{
	// if current line is empty we return ""
	if (current_line.empty()) return "";

	// we subtring to separate the comp from everything prev = and post ;
	size_t start = current_line.find('=');
	size_t length = current_line.find(';');

	start = (start != std::string::npos) ? start + 1 : 0;
	length = (length != std::string::npos) ? length - start : std::string::npos;

	std::string comp = current_line.substr(start, length);

	// and lastly, we return the comp
	return comp;
}

std::string Parser::jump()
{
	if (current_line.empty()) return "";
	
	// jump requires a semicolon symbol
	size_t se_pos = current_line.find(';');
	if (se_pos == std::string::npos) return "";

	// we get the isolated jump comparison
	std::string jump = current_line.substr(se_pos + 1);

	return jump;
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
			// We add the .asm if the user didn't specified it.
			if (path.length() < 4 || path.substr(path.length() - 4) != ".asm") path += ".asm";
			break;

		default:
			throw std::runtime_error("Error: more than one argument provided '" + std::string(argv[2]) + "'");
	}
	return path;
}

bool Parser::is_all_digits(const std::string& symbol)
{
	if (symbol.empty()) return false;

	for (char c : symbol)
		if (!std::isdigit(static_cast<unsigned char>(c)))
			return false;
	
	return true;
}

bool Parser::is_valid_char(const std::string& symbol)
{
	if (symbol.empty()) return false;

	// If starts with a number, it's wrong
	if (std::isdigit(static_cast<unsigned char>(symbol[0]))) return false;

	for (char c : symbol)
		// if it's either alphanumeric or one of those symbols
		if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '.' || c == '$' || c == ':'))
			return false;
		
	return true;
}