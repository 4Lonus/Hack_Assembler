#include "Parser.hpp"
#include "SymbolTable.hpp"
#include "Code.hpp"

#include <iostream>
#include <bitset>

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
			if (par.advance().empty()) continue;

			if (par.instruction_type() == InstructionType::E_INSTRUCTION)
				throw std::runtime_error("Error: Invalid Instruction '" + std::to_string(current_address) + "' ('" + par.get_current_line() + "')");

			// If it's Label
			else if (par.instruction_type() == InstructionType::L_INSTRUCTION)
			{
				std::cout << "Label: " << par.get_current_line() << std::endl;

				if (table.contains(par.symbol())) continue;

				table.add_entry(par.symbol(), current_address);
			}
			else if (par.instruction_type() == InstructionType::A_INSTRUCTION || par.instruction_type() == InstructionType::C_INSTRUCTION)
				current_address++;
		}

		/*			SECOND PASS			*/
		// we write in the same folder with same name, only changin the extention
		std::string output_path = program_path.substr(0, program_path.find_last_of('.')) + ".hack";
		std::ofstream output_file(output_path);

		if (!output_file.is_open()) throw std::runtime_error("Error: could not write output file '" + output_path + "'");

		par.reset();
		int next_variable_address = 16;

		while (par.has_more_lines())
		{
			if (par.advance().empty()) continue;

			std::string bin;

			// If it's NOT Label
			if (par.instruction_type() != InstructionType::L_INSTRUCTION)
			{
				std::cout << "2nd Passing: " << par.get_current_line() << std::endl;
				
				// "If the instruction is  @symbol" (A)
				if (par.instruction_type() == InstructionType::A_INSTRUCTION)
				{
					std::string symbol = par.symbol();

					int symbol_value;

					// is a direct value?
					if (Parser::is_all_digits(symbol))
					{
						try {symbol_value = std::stoi(symbol);}
						catch (const std::out_of_range&) {throw std::runtime_error("Error: A instruction out of range '" + symbol + "'");}
					}

					// is a symbol?
					else
					{
						// "If symbol is not in the symbol table, adds it to the table"
						if(!table.contains(symbol))
						{
							table.add_entry(symbol, next_variable_address);
							next_variable_address++;
						}
						symbol_value = table.get_address(symbol);
					}

					if (symbol_value < 0 || 32767 < symbol_value)
						throw std::runtime_error("Error: A instruction value should be between 0 and 32767, it is '" + std::to_string(symbol_value) + "'");

					// "Translates the symbol into its binary value"
					bin = "0" + std::bitset<15>(symbol_value).to_string();
				}
				// "If the instruction is  dest=comp;jump" (C)
				else if (par.instruction_type() == InstructionType::C_INSTRUCTION)
				{
					std::string bin_dest = Code::dest(par.dest());
					std::string bin_comp = Code::comp(par.comp());
					std::string bin_jump = Code::jump(par.jump());

					if (bin_dest.empty() || bin_comp.empty() || bin_jump.empty())
						throw std::runtime_error("Error: Invalid C-Instruction");
					
					bin = "111" + bin_comp + bin_dest + bin_jump;
				}

				// We write in the output file
				output_file << bin << std::endl;
			}
		}

		// aaaaaand we close the file
		output_file.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}