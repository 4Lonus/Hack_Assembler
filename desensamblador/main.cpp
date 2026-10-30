#include "Parser.hpp"
#include "SymbolTable.hpp"
#include "Code.hpp"

#include <iostream>


int main(int argc, char* argv[])
{
	try
	{
		/*			INITIALIZATION			*/
		size_t instruction_count = 0;
		// Open file.
		auto program_path = Parser::parse_args(argc, argv);
		Parser par(program_path);

		// Creates Symbol Table (which in this case works almost only for labels)
		Symbol_Table table;

		/*			ZERO PASS			*/
		while (par.has_more_lines()) {par.advance(); instruction_count++;}
		par.reset();

		/*			FIRST PASS			*/
		int current_address = 0;
	
		std::string last_A_instruction = "";
		bool last_instruction_was_A = false;

		while (par.has_more_lines())
		{
			if (par.advance().empty())
				throw std::runtime_error("Error: empty line at '" + std::to_string(current_address) + "'");
			
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
					uint16_t direction = std::stoi(last_A_instruction.substr(1), nullptr, 2);

					// We must check if it's inside the symbol table.
					if (!table.contains(direction) && direction < instruction_count) table.add_entry(direction);
				}
				last_instruction_was_A = false;
			}
			current_address++;
		}

		/*			SECOND PASS			*/
		// we write in the same folder with same name, only changin the extention
		std::string output_path = program_path.substr(0, program_path.find_last_of('.')) + ".asm";
		std::ofstream output_file(output_path);

		if (!output_file.is_open()) throw std::runtime_error("Error: could not write output file '" + output_path + "'");

		current_address = 0;
		par.reset();

		while (par.has_more_lines())
		{
			par.advance();

			// We output the label to the file
			if (table.contains(current_address)) output_file << "(" << table.get_symbol(current_address) << ")" << std::endl;

			// If it's instruction A, and it's on the table we use the symbol instead.
			if (par.instruction_type() == InstructionType::A_INSTRUCTION)
			{
				uint16_t value = par.value_A();

				if (table.contains(value))
					output_file << "@" << table.get_symbol(value) << std::endl;

				else output_file << "@" << value << "\n";
			}
			else
			{
				std::string d = Code::dest(par.dest());
				std::string c = Code::comp(par.comp());
				std::string j = Code::jump(par.jump());

				if (!d.empty()) output_file << d << "=";
				output_file << c;
				if (!j.empty()) output_file << ";" << j;
				output_file << std::endl;
			}

			current_address++;
		}

		// aaaaaAAAAAAAAAAAAand we close the file (again)
		output_file.close();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}