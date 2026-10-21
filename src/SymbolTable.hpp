#ifndef HACK_ASSEMBLER_SYMBOL_TABLE
#define HACK_ASSEMBLER_SYMBOL_TABLE

#include <fstream>
#include <unordered_map>

class Symbol_Table
{
	std::unordered_map<std::string, int> table;
public:
	Symbol_Table();
	void add_entry(std::string symbol, int address);
	bool contains(std::string symbol);
	int get_address(std::string symbol);
};

#endif