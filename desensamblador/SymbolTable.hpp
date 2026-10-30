#ifndef HACK_DISASSEMBLER_SYMBOL_TABLE
#define HACK_DISASSEMBLER_SYMBOL_TABLE

#include <fstream>
#include <map>
#include <cstdint>

class Symbol_Table
{
	std::map<uint16_t, std::string> table;

	int label_number;
public:
	Symbol_Table();
	void add_entry(uint16_t address, std::string symbol);
	void add_entry(uint16_t address);
	bool contains(uint16_t address);
	std::string get_symbol(uint16_t address);
};

#endif