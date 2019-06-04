#ifndef COMMAND_DETAILS_HPP
#define COMMAND_DETAILS_HPP

#include <string>
#include <map>

class CommandDetails
{
public:
	std::string title;
	std::string command;
	std::map<std::string, std::string> arguments;
	void clear();
};

#endif