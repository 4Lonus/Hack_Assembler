#include "Code.hpp"

std::string Code::comp(std::string comp_bin)
{
	auto str = comp_table.find(comp_bin);

	// if it not found
	if (str != comp_table.end())
		return str->second;
	return "";
}

std::string Code::dest(std::string dest_bin)
{
	auto str = dest_table.find(dest_bin);

	// if it not found
	if (str != dest_table.end())
		return str->second;
	return "";
}

std::string Code::jump(std::string jump_bin)
{
	auto str = jump_table.find(jump_bin);

	// if it not found
	if (str != jump_table.end())
		return str->second;
	return "";
}