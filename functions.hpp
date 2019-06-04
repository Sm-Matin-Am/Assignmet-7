#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "film.hpp"
#include "constValues.hpp"
#include <vector>
#include <string>

std::vector<std::string> separateInput(std::string inputLine);

std::string readLine(int& foundCharPlace, std::string inputLine, int previousPlace);

void findArgument(std::vector<std::string> listOfArgs, std::map<std::string, std::string>::iterator arg, 
															  std::vector<std::string>& sortedArguments);

std::string getArgument(std::string arg, std::map<std::string, std::string> map);

void deleteWhiteSpacesAtBegin(std::string& input);

void deleteWhiteSpacesAtEnd(std::string& input);

std::vector<Film*> search(std::vector<Film*> films, std::string name, int price, 
										  int min_year, int max_year, 
										  int min_rate, std::string director);

#endif