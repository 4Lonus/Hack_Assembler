#include "Code.hpp"

std::string Code::comp(std::string comp_str)
{
	auto bin = comp_table.find(comp_str);

	// if it not found
	if (bin != comp_table.end())
		return bin->second;
	return "";
}

std::string Code::dest(std::string dest_str)
{
	auto bin = dest_table.find(dest_str);

	// if it not found
	if (bin != dest_table.end())
		return bin->second;
	return "";
}

std::string Code::jump(std::string jump_str)
{
	auto bin = jump_table.find(jump_str);

	// if it not found
	if (bin != jump_table.end())
		return bin->second;
	return "";
}