#include "Parser.hpp"
#include "SymbolTable.hpp"
#include "Code.hpp"

#include <iostream>


int main(int argc, char* argv[])
{
	try
	{
		/*			INITIALIZATION			*/
		size_t number_of_lines = 0;
		// Open file.
		auto program_path = Parser::parse_args(argc, argv);
		Parser par(program_path);

		// Creates Symbol Table
		Symbol_Table table;

		/*			ZERO PASS			*/
		while (par.has_more_lines()) {par.advance(); number_of_lines++;}
		par.reset();

		/*			FIRST PASS			*/
		int current_address = 0;
	
		std::string last_A_instruction = "";
		bool last_instruction_was_A = false;

		while (par.has_more_lines())
		{
			if (par.advance().empty())
				throw std::runtime_error("Error: empty line at '" + std::to_string(current_address) + "'");

			if (par.instruction_type() == InstructionType::E_INSTRUCTION)
				throw std::runtime_error("Error: Invalid Instruction '" + std::to_string(current_address) + "' ('" + par.get_current_line() + "')");
			
			else if (par.instruction_type() == InstructionType::A_INSTRUCTION)
			{
				last_A_instruction = par.get_current_line();
				last_instruction_was_A = true;
			}
			else if (par.instruction_type() == InstructionType::C_INSTRUCTION)
			{
				bool has_jump = par.jump() != "000";

				if (last_instruction_was_A && has_jump)
				{
					int direction = std::stoi(last_A_instruction.substr(1), nullptr, 2);

					// We must check if it's inside the symbol table.
					if (!table.contains(direction) && direction < number_of_lines) table.add_entry(direction);
				}
				last_instruction_was_A = false;
			}
			current_address++;
		}

		/*			SECOND PASS			*/

		// We translate each instruction
		// If it's instruction A, and it's on the table we use the symbol instead.
		// If current line is in the Symbol table, we input a (Label) first and only then the actual instruction.
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}