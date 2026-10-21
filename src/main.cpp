#include "Parser.hpp"
#include "SymbolTable.hpp"

#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		/*			INITIALIZATION			*/

		// We parse the path to the file & open the program
		auto program_path = Parser::parse_args(argc, argv);
		Parser par(program_path);

		// We Initialize the smbol table.

		Symbol_Table table;

		/*			FIRST PASS			*/
		int current_address = 0;
		while (par.has_more_lines())
		{
			par.advance();
			if (par.get_current_line().empty()) continue;

			std::cout << "Parsing: " << par.get_current_line() << std::endl;

			if (par.instruction_type() == InstructionType::E_INSTRUCTION)
				throw std::runtime_error("Error: Invalid Instruction '" + std::to_string(current_address) + "'");

			// If it's Label
			else if (par.instruction_type() == InstructionType::L_INSTRUCTION)
			{
				if (table.contains(par.symbol())) continue;

				table.add_entry(par.symbol(), current_address);
			}
			else if (par.instruction_type() == InstructionType::A_INSTRUCTION || par.instruction_type() == InstructionType::C_INSTRUCTION)
				current_address++;
		}

		/*			SECOND PASS			*/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}