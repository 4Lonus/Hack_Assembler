#include "SymbolTable.hpp"

// We initialize with the predefined symbols
Symbol_Table::Symbol_Table() : label_number(0)
{
	label_number = 0;

	// R entries
	for (size_t i = 0; i < 16; i++)
	{
		std::string r_symbol = "R" + std::to_string(i);
		add_entry(i, r_symbol);
	}
	
	// Input / Output
	add_entry(16384, "SCREEN");
	add_entry(24576, "KBD");
}

// all methods pretty self explanatory

void Symbol_Table::add_entry(uint16_t address, std::string symbol)
{
	table[address] = symbol;
}

void Symbol_Table::add_entry(uint16_t address)
{
	std::string symbol = "L" + std::to_string(label_number++);

	table[address] = symbol;
}

bool Symbol_Table::contains(uint16_t address)
{
	return table.find(address) != table.end();
}

std::string Symbol_Table::get_symbol(uint16_t address)
{
	return table.at(address);
}