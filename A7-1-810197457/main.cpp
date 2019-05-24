#include <iostream>
#include <string>
#include "classes.hpp"
#include "systemInterface.hpp"

int main()
{
	SystemInterface si;
	std::string inputCommand;

	while (getline(std::cin, inputCommand))
			si.processInput(inputCommand);
}