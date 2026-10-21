#include "SymbolTable.hpp"

// We initialize with the predefined symbols
Symbol_Table::Symbol_Table()
{
	// R entries
	for (size_t i = 0; i < 16; i++)
	{
		std::string r_symbol = "R" + std::to_string(i); // is this valid?
		add_entry(r_symbol, i);
	}
	
	// Input / Output
	add_entry("SCREEN", 16384);
	add_entry("KBD", 24576);
	add_entry("SP", 0);

	// VM Stuff
	add_entry("LCL", 1);
	add_entry("ARG", 2);
	add_entry("THIS", 3);
	add_entry("THAT", 4);
}

// all methods pretty self explanatory

void Symbol_Table::add_entry(std::string symbol, int address)
{
	table[symbol] = address;
}

bool Symbol_Table::contains(std::string symbol)
{
	return table.find(symbol) != table.end();
}

int Symbol_Table::get_address(std::string symbol)
{
	return table.at(symbol);
}