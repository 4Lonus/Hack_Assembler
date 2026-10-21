#ifndef HACK_ASSEMBLER_SYMBOLTABLE
#define HACK_ASSEMBLER_SYMBOLTABLE

#include <fstream>
#include <unordered_map>

class Symbol_Table
{
public:
	std::unordered_map<std::string, int> table;

	Symbol_Table();
	void add_entry(std::string symbol, int address);
	bool contains(std::string symbol);
	int get_address(std::string symbol);
};

#endif