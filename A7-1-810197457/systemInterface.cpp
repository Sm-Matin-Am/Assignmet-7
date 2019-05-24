#include <iostream>
#include <vector>
#include <string>
#include "classes.hpp"
#include "systemInterface.hpp"
#include "film.hpp"
#include "customer.hpp"
#include "publisher.hpp"
#include "idSeter.hpp"
#include "bank.hpp"
#include "commandDetails.hpp"
#include "filmRepository.hpp"
#include "functions.hpp"
#include "constValues.hpp"
#include "searchArguments.hpp"
#include "message.hpp"
#include "exceptions.cpp"

Customer* NO_USER = new Customer("-", "-", "-", 0, 0);

SystemInterface::SystemInterface(void)
	: currentUser(NO_USER)
{
	idManager = new IdSeter();
	money = 0;
}

void SystemInterface::processInput(std::string inputCommand)
{
	deleteWhiteSpacesAtBegin(inputCommand);
	deleteWhiteSpacesAtEnd(inputCommand);
	try {
		this->analizeInput(inputCommand);
		this->processCommand();
	} catch (std::exception* ex) {
		std::cout << ex->what() << std::endl;
	}
	commandDetails.clear();
}

void SystemInterface::checkTitleOfCommand(std::string _title)
{
	for (int j = 0; j < CORRECT_COMMAND_TITLES.size(); ++j)
		if (_title == CORRECT_COMMAND_TITLES[j]) {
			commandDetails.title = _title;
			return;
		}
	throw new BadRequest();
}

void SystemInterface::processCommand(void)
{
	if (commandDetails.title == POST)
		this->processPostCommands();
	else if (commandDetails.title == PUT)
		this->processPutCommands();
	else if (commandDetails.title == DELETE)
		this->processDeleteCommands();
	else if (commandDetails.title == GET)
		this->processGetCommands();
	else
		throw new BadRequest();
}

void SystemInterface::processPostCommands(void)
{
	std::string commandText = commandDetails.command;
	if (commandText == "signup")
		this->signup();
	else if (commandText == "login")
		this->login();
	else if (commandText == "films")
		this->addFilm();
	else if (commandText == "money") {
		if (commandDetails.arguments.empty())
			currentUser->increaseMoney(this->accounts.withdraw(currentUser->getId()));
		else {
			currentUser->increaseMoney(std::stoi(commandDetails.arguments.begin()->second));
			std::cout << "OK" << std::endl;
		}
	}
	else if (commandText == "replies") {
		std::vector<std::string> sortedArguments = this->sortArguments(REPLAY_ARGUMENTS);
		currentUser->replayComment(std::stoi(sortedArguments[0]), std::stoi(sortedArguments[1]), sortedArguments[2]);
	}
	else if (commandText == "followers")
		this->followPub(std::stoi(commandDetails.arguments.begin()->second));
	else if (commandText == "buy")
		this->sellFilm();
	else if (commandText == "rate")
		this->rateFilm();
	else if (commandText == "comments")
		this->putComment();
	else
		throw new NotFound();
}

void SystemInterface::processPutCommands(void)
{
	if (commandDetails.command == "films") {
		currentUser->editFilm(commandDetails.arguments);
		std::cout << "OK" << std::endl;
	}
	else
		throw new NotFound();
}

void SystemInterface::processDeleteCommands(void)
{
	if (commandDetails.command == "films") {
		this->findFilmById(std::stoi(commandDetails.arguments.begin()->second));
		currentUser->deleteFilm(std::stoi(commandDetails.arguments.begin()->second));
		filmBox.deleteFilm(std::stoi(commandDetails.arguments.begin()->second));
	}
	else if (commandDetails.command == "comments") {
		std::vector<std::string> sortedArguments = sortArguments(DELETE_COMMENT);
		currentUser->deleteComment(std::stoi(sortedArguments[0]), std::stoi(sortedArguments[1]));
	}
	else
		throw new NotFound();
	std::cout << "OK" << std::endl;
}

void SystemInterface::processGetCommands(void)
{
	if (commandDetails.command == "followers")
		currentUser->showFollowers();
	else if (commandDetails.command == "published")
		this->searchFilms(currentUser->getPublishedFilms());
	else if (commandDetails.command == "films")
			this->searchFilms(filmBox.getFilms());
	else if (commandDetails.command == "purchased")
		this->searchFilms(currentUser->getPurchasedFilms());
	else if (commandDetails.command == "notifications")
		currentUser->showUnreadMessages();
	else if (commandDetails.command == "notifications read")
		currentUser->showMessages(std::stoi(commandDetails.arguments.begin()->second));
	else
		throw new NotFound();
}

void SystemInterface::searchFilms(std::vector<Film*> films)
{
	if (!commandDetails.arguments.empty() && commandDetails.arguments.begin()->first == "film_id") {
		this->findFilmById(std::stoi(commandDetails.arguments.begin()->second))->showDetails();
		filmBox.showTopFilms(currentUser);
		return;
	}
	std::vector<std::string> sortedArguments = sortArguments(SEARCH_FIELDS);
	for (int k = 0; k < BLANK_FIELDS.size(); k++)
		if (sortedArguments[k].empty())
			sortedArguments[k] = BLANK_FIELDS[k];
	std::vector<Film*> searchResault = search(films, sortedArguments[0], std::stoi(sortedArguments[1]),
		std::stoi(sortedArguments[2]), std::stoi(sortedArguments[3]),
		std::stoi(sortedArguments[4]), sortedArguments[5]);
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	for (int j = 0; j < searchResault.size(); ++j) {
		std::cout << j + 1 << ". ";
		searchResault[j]->printInfo();
	}
}

void SystemInterface::sellFilm(void)
{
	Film* film = this->findFilmById(std::stoi(commandDetails.arguments.begin()->second));
	currentUser->buyFilm(film);
	this->calcPortionOfSystem(film);
	std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " buy your film " + film->getName() + "with id " + std::to_string(film->getId()) + ".";
	Message* newMessage = new Message(messageContent);
	film->getPub()->recieveMessage(newMessage);
	std::cout << "OK" << std::endl;
}

void SystemInterface::putComment(void)
{
	std::vector<std::string> sortedArguments = this->sortArguments(COMMENT_ARGUMENTS);
	Film* film = findFilmById(std::stoi(sortedArguments[0]));
	if (currentUser->alreadyHasBoughtFilm(film)) {
		film->addNewComment(sortedArguments[1], idManager->makeNewCommentId(film->getId()), currentUser);
		std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " comment on your film " + film->getName() + " with id " + std::to_string(film->getId());
		Message* newMessage = new Message(messageContent);
		film->getPub()->recieveMessage(newMessage);
	}
	else
		throw new PermissionDenied();
	std::cout << "OK" << std::endl;
}

void SystemInterface::checkAccessibilityLevel(void)
{
	if (currentUser == NO_USER && commandDetails.command != "signup" && commandDetails.command != "login")
		throw new PermissionDenied();
}

void SystemInterface::checkBodyOfCommand(std::string commandBody)
{
	for (int k = 0; k < CORRECT_COMMAND_BODIES.size(); ++k)
		if (commandBody == CORRECT_COMMAND_BODIES[k]) {
			commandDetails.command = commandBody;
			return;
		}
	throw new NotFound();
}

void SystemInterface::checkDuplicationOfUsername(std::string newUsername)
{
	for (int i = 0; i < registeredCustomers.size(); i++)
		if (registeredCustomers[i]->getUsername() == newUsername)
			throw new BadRequest();
	return;
}

void SystemInterface::signup(void)
{
	std::vector<std::string> sortedArguments = this->handleSignupErrors();
	int userId;
	std::string customerType = getArgument("publisher", commandDetails.arguments);
	if (customerType == ARG_NOT_FOUND || customerType == "false") {
		userId = idManager->makeNewUserId();
		currentUser = new Customer(sortedArguments[0], sortedArguments[1], sortedArguments[2], std::stoi(sortedArguments[3]), userId);
	}
	else if (customerType == "true") {
		userId = idManager->makeNewUserId();
		currentUser = new Publisher(sortedArguments[0], sortedArguments[1], sortedArguments[2], std::stoi(sortedArguments[3]), userId);
	}
	else
		throw new BadRequest();
	
	registeredCustomers.push_back(currentUser);
	accounts.addAccount(userId);
	std::cout << "OK" << std::endl;
}

void SystemInterface::login(void)
{
	std::vector<std::string> sortedArguments = sortArguments(LOGIN_ARGUMENTS);
	if (sortedArguments.size() != 2)
		throw new BadRequest();
	for (int j = 0; j < registeredCustomers.size(); j++)
		if (registeredCustomers[j]->checkLoginInfo(sortedArguments[0], sortedArguments[1])) {
				currentUser = registeredCustomers[j];
				std::cout << "OK" << std::endl;
				return;
			}
}

std::vector<std::string> SystemInterface::handleSignupErrors()
{
	std::vector<std::string> sortedArguments = sortArguments(SIGNUP_ARGUMENTS);
	if (sortedArguments.size() != 4 && sortedArguments.size() != 5)
		throw new BadRequest();
	this->checkDuplicationOfUsername(sortedArguments[1]);
	return sortedArguments;
}

std::vector<std::string> SystemInterface::sortArguments(std::vector<std::string> neededArguments)
{
	std::vector<std::string> sortedArguments;
	for (int j = 0; j < neededArguments.size(); j++)
		sortedArguments.push_back("");
	for (auto itr = commandDetails.arguments.begin(); itr != commandDetails.arguments.end(); itr++)
		findArgument(neededArguments, itr, sortedArguments);
	return sortedArguments;	
}

void SystemInterface::addFilm(void)
{
	std::vector<std::string> sortedArguments = this->sortArguments(FILM_ARGUMENTS);
	for (int i = 0; i < sortedArguments.size(); i++)
		if (sortedArguments[i].empty())
			throw new BadRequest();
	Film* newFilm = currentUser->addFilm(sortedArguments);
	newFilm->setId(idManager->makeNewFilmId());
	filmBox.addFilm(newFilm);
	std::cout << "OK" << std::endl;
}

void SystemInterface::followPub(int id)
{
	for (int i = 0; i < registeredCustomers.size(); ++i)
		if (registeredCustomers[i]->getId() == id) {
			currentUser->follow(registeredCustomers[i]);
			return;
		}
	throw new NotFound();
}

Film* SystemInterface::findFilmById(int id)
{
	for (int i = 0; i < filmBox.getFilms().size(); i++)
		if (filmBox.getFilms()[i]->getId() == id)
			return filmBox.getFilms()[i];
	throw new NotFound();
}

void SystemInterface::calcPortionOfSystem(Film* film)
{
	double ratio = film->getFilmStatus();
	money += film->getPrice() * (1 - ratio);
	accounts.deposite(film->getPub()->getId(), film->getPrice() * ratio);
}

void SystemInterface::rateFilm(void)
{
	std::vector<std::string> sortedArguments = this->sortArguments(RATE_ARGUMENTS);
	Film* film = findFilmById(std::stoi(sortedArguments[0]));
	if (currentUser->alreadyHasBoughtFilm(film)) {
		film->addScore(currentUser->getId(), std::stoi(sortedArguments[1]));
		std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " rate your film " + film->getName() + "with id " + std::to_string(film->getId()) + ".";
		Message* newMessage = new Message(messageContent);
		film->getPub()->recieveMessage(newMessage);
	}
	else
		throw new PermissionDenied();
	std::cout << "OK" << std::endl;
}

void handleInputErrors(std::vector<std::string> separatedCommand)
{
	if ((!(separatedCommand.size() % 2) && separatedCommand.size() != 0) || separatedCommand.size() == 3 || separatedCommand.size() == 5)
		return;
	throw new BadRequest();  
}

void SystemInterface::analizeInput(std::string inputCommand)
{
	std::vector<std::string> separatedCommand = separateInput(inputCommand);
	handleInputErrors(separatedCommand);

	this->checkTitleOfCommand(separatedCommand[0]);
	this->checkBodyOfCommand(separatedCommand[1]);

	if (inputCommand.find('?') != std::string::npos && separatedCommand.size() > 2)
		for (int k = 2; k < separatedCommand.size(); k += 2) {
			commandDetails.arguments.insert(std::pair<std::string, std::string>(separatedCommand[k], separatedCommand[k + 1]));
		}

	this->checkAccessibilityLevel();
}