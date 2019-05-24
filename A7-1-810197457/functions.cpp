#include "functions.hpp"
#include "classes.hpp"
#include "exceptions.cpp"
#include "searchArguments.hpp"
#include "constValues.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> separateInput(std::string inputLine)
{
	std::vector<std::string> separatedCommand;
	std::string separatedPiece;
	int foundCharPlace = 0, previousPlace = -1;
	
	while (foundCharPlace != -1)
	{
		separatedPiece = readLine(foundCharPlace, inputLine, previousPlace);

		if (separatedPiece != "?")
			separatedCommand.push_back(separatedPiece);

		previousPlace = foundCharPlace;
	}
	return separatedCommand;
}

std::string readLine(int& foundCharPlace, std::string inputLine, int previousPlace)
{
	std::string separatedPiece;
	foundCharPlace = inputLine.find_first_of(' ', foundCharPlace + 1);
	separatedPiece = inputLine.substr(previousPlace + 1, foundCharPlace - previousPlace - 1);
	if (separatedPiece == "notifications" && foundCharPlace != -1)
		separatedPiece += " " + readLine(foundCharPlace, inputLine, foundCharPlace);
	return separatedPiece;
}

void findArgument(std::vector<std::string> listOfArgs, std::map<std::string, std::string>::iterator arg, 
															  std::vector<std::string>& sortedArguments)
{
	for (int i = 0; i < listOfArgs.size(); ++i)
		if (listOfArgs[i] == arg->first) {
			sortedArguments[i] = arg->second;
			return;
		}
	if (arg->first != "Publisher")
		throw new BadRequest();
	return;
}

std::string getArgument(std::string arg, std::map<std::string, std::string> map)
{
	for (auto itr = map.begin(); itr != map.end(); ++itr)
		if (arg == itr->first)
			return itr->second;
	return ARG_NOT_FOUND;
}

void deleteWhiteSpacesAtBegin(std::string& input)
{
	while (input[0] == ' ')
		input.erase(input.begin());
}
void deleteWhiteSpacesAtEnd(std::string& input)
{
	while (input[input.size() - 1] == ' ') 
		input.erase(input.end() - 1);
}

std::vector<Film*> search(std::vector<Film*> films, std::string name, int price, 
										  int min_year, int max_year, 
										  int min_rate, std::string director)
{
	std::vector<Film*> searchResault = films;
	for (int i = 0; i < films.size(); i++)
		if (!films[i]->checkFilters(name, price, min_year, max_year, min_rate, director))
			searchResault.erase(searchResault.begin() + i);
	return searchResault;
}