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

Customer* ADMIN = new Customer("admin@admin.com", "admin", "admin", 0, 0);

SystemInterface::SystemInterface(void)
	: currentUser(NULL)
{
	registeredCustomers.push_back(ADMIN);
	idManager = new IdSeter();
	money = 0;
}

void SystemInterface::checkIfSystemIsFree(void)
{
	if (currentUser != NULL)
		throw new BadRequest();
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
	else if (commandDetails.title == GET)
		this->processGetCommands();
	else
		throw new BadRequest();
}

int SystemInterface::findPostCommand(void)
{
	for (int k = 0; k < POST_COMMANDS.size(); k++)
		if (commandDetails.command == POST_COMMANDS[k])
			return k;
	throw new NotFound();
}

void SystemInterface::processPostCommands(void)
{
	switch(this->findPostCommand()) 
	{
		// case SIGNUP: this->signup(); break;
        // case LOGIN: this->login(); break;
		// case FILMS: this->addFilm(); break;
		case MONEY:
			if (commandDetails.arguments.empty())
				currentUser->increaseMoney(this->accounts.withdraw(currentUser->getId()));
			else
				currentUser->increaseMoney(std::stoi(commandDetails.arguments.begin()->second));
			break;
		case REPLIES: 
		{
			std::vector<std::string> sortedArguments = this->sortArguments(REPLAY_ARGUMENTS);
			currentUser->replayComment(std::stoi(sortedArguments[0]), std::stoi(sortedArguments[1]), sortedArguments[2]);
			break;
		}
		case FOLLOWERS:
			this->followPub(std::stoi(commandDetails.arguments.begin()->second)); break;
		// case BUY: this->sellFilm(); break;
		// case RATE: this->rateFilm(); break;
		case COMMENTS: this->putComment(); break;
		case PUT_FILMS:
			currentUser->editFilm(commandDetails.arguments); break;
		// case DELETE_FILMS:
		// {
			// this->findFilmById(std::stoi(commandDetails.arguments.begin()->second));
			// currentUser->deleteFilm(std::stoi(commandDetails.arguments.begin()->second));
			// filmBox.deleteFilm(std::stoi(commandDetails.arguments.begin()->second));
		// 	break;
		// }
		case DELETE_COMMENTS:
		{
			std::vector<std::string> sortedArguments = sortArguments(DELETE_COMMENT);
			currentUser->deleteComment(std::stoi(sortedArguments[0]), std::stoi(sortedArguments[1]));
			break;
		}
		// case LOGOUT: this->logout(); break;
		default: break;
	}
	std::cout << "OK" << std::endl;
}

void SystemInterface::removeFilm(int filmId)
{
	this->findFilmById(filmId);
	currentUser->deleteFilm(filmId);
	filmBox.deleteFilm(filmId);
}

void SystemInterface::processGetCommands(void)
{
	if (commandDetails.command == "followers")
		currentUser->showFollowers();
	// else if (commandDetails.command == "published")
	// 	this->searchFilms(currentUser->getPublishedFilms());
	// else if (commandDetails.command == "films")
	// 		this->searchFilms(filmBox.getFilms());
	// else if (commandDetails.command == "purchased")
	// 	this->searchFilms(currentUser->getPurchasedFilms());
	else if (commandDetails.command == "notifications")
		currentUser->showUnreadMessages();
	else if (commandDetails.command == "notifications read")
		currentUser->showMessages(std::stoi(commandDetails.arguments.begin()->second));
	else if (commandDetails.command == "money")
		currentUser->getBalance();
	else
		throw new NotFound();
}

// std::vector<Film*> SystemInterface::getAllFilms(void) { return filmBox.getFilms(); }

void SystemInterface::searchFilms(std::vector<Film*> films, std::string director)
{
	commandDetails.arguments.insert(std::pair<std::string, std::string>("director", director));
	std::vector<std::string> sortedArguments = sortArguments(SEARCH_FIELDS);
	for (int k = 0; k < BLANK_FIELDS.size(); k++)
		if (sortedArguments[k].empty())
			sortedArguments[k] = BLANK_FIELDS[k];
	std::vector<Film*> searchResault = search(films, sortedArguments[0], std::stoi(sortedArguments[1]),
											  std::stoi(sortedArguments[2]), std::stoi(sortedArguments[3]),
											  std::stoi(sortedArguments[4]), sortedArguments[5]);////////////////////////////////////////////////////////////////////
}

void SystemInterface::sellFilm(int filmId)
{
	Film* film = this->findFilmById(filmId);
	currentUser->buyFilm(film);
	filmBox.updateElements(film->getId(), currentUser);
	this->calcPortionOfSystem(film);
	std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " buy your film " + film->getName() + " with id " + std::to_string(film->getId()) + ".";
	Message* newMessage = new Message(messageContent);
	film->getPub()->recieveMessage(newMessage);
}

void SystemInterface::putComment(void)
{
	std::vector<std::string> sortedArguments = this->sortArguments(COMMENT_ARGUMENTS);
	Film* film = findFilmById(std::stoi(sortedArguments[0]));
	if (currentUser->alreadyHasBoughtFilm(film->getId())) {
		film->addNewComment(sortedArguments[1], idManager->makeNewCommentId(film->getId()), currentUser);
		std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " comment on your film " + film->getName() + " with id " + std::to_string(film->getId()) + ".";
		Message* newMessage = new Message(messageContent);
		film->getPub()->recieveMessage(newMessage);
	}
	else
		throw new PermissionDenied();
}

void SystemInterface::checkAccessibilityLevel(void)
{
	if (currentUser == NULL && commandDetails.command != "signup" && commandDetails.command != "login")
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
}

int SystemInterface::signup(std::string email, std::string username, std::string password, std::string age, std::string accountType)
{
	this->handleSignupErrors(email, username, password, age);

	if (accountType == "publisher")
		currentUser = new Publisher(email, username, password, std::stoi(age), idManager->makeNewUserId());
	else
		currentUser = new Customer(email, username, password, std::stoi(age), idManager->makeNewUserId());
	
	registeredCustomers.push_back(currentUser);
	accounts.addAccount(currentUser->getId());

	return currentUser->getId();
}

int SystemInterface::login(std::string username, std::string password)
{
	this->checkIfSystemIsFree();//******************************************************************************************************************************************************************************************************************************************************************************************************************NULL

	for (int j = 0; j < registeredCustomers.size(); j++)
		if (registeredCustomers[j]->checkLoginInfo(username, password)) {
				currentUser = registeredCustomers[j];
				return currentUser->getId();
			}
	throw new BadRequest();
}

void SystemInterface::logout(void) 
{ 
	if (currentUser != NULL)
		currentUser = NULL;
	else
		throw new BadRequest();
}

void SystemInterface::handleSignupErrors(std::string email, std::string username, std::string password, std::string age)
{
	this->checkIfSystemIsFree();

	if (email.empty() || username.empty() || password.empty() || age.empty())
		throw new BadRequest();
	
	this->checkDuplicationOfUsername(username);
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

void SystemInterface::addFilm(std::string name, std::string year, std::string length, 
							  std::string price, std::string summary, std::string director)
{
	// std::vector<std::string> sortedArguments = this->sortArguments(FILM_ARGUMENTS);
	// for (int i = 0; i < sortedArguments.size(); i++)
	if (name.empty() || year.empty() || length.empty() || price.empty() || summary.empty() || director.empty())
		throw new BadRequest();
	Film* newFilm = currentUser->addFilm(name, year, length, price, summary, director, idManager->makeNewFilmId());
	// newFilm->setId(idManager->makeNewFilmId());
	filmBox.addFilm(newFilm);
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

Customer* SystemInterface::findUserById(int id)
{
	for (int i = 0; i < registeredCustomers.size(); i++)
		if (registeredCustomers[i]->getId() == id)
			return registeredCustomers[i];
	throw new NotFound();
}

void SystemInterface::calcPortionOfSystem(Film* film)
{
	double ratio = film->getFilmStatus();
	money += film->getPrice() * (1 - ratio);
	accounts.deposite(film->getPub()->getId(), film->getPrice() * ratio);
}

void SystemInterface::rateFilm(int filmId, int score)
{
	// std::vector<std::string> sortedArguments = this->sortArguments(RATE_ARGUMENTS);
	Film* film = findFilmById(filmId);
	// if (currentUser->alreadyHasBoughtFilm(film->getId())) {
		film->addScore(currentUser->getId(), score);
		std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " rate your film " + film->getName() + " with id " + std::to_string(film->getId()) + ".";
		Message* newMessage = new Message(messageContent);
		film->getPub()->recieveMessage(newMessage);
	// }
	// else
		// throw new PermissionDenied();
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
	if (currentUser == ADMIN && commandDetails.title == "GET" && commandDetails.command == "money") {
		std::cout << money << std::endl;
		return;
	}
	this->checkAccessibilityLevel();
}

void SystemInterface::setSalableFilms(int budget, std::string director)
{
	listedSalableFilms.clear();
	for (int j = 0; j < filmBox.getFilms().size(); j++)
		if (filmBox.getFilms()[j]->getPrice() <= budget && (filmBox.getFilms()[j]->getDirector() == director || director.empty()))
			listedSalableFilms.push_back(filmBox.getFilms()[j]);
}

void SystemInterface::setPublishedFilms(std::vector<Film*> films, std::string director)
{
	listedPublishedFilms.clear();
	for (int k = 0; k < films.size(); k++)
		if (films[k]->getDirector() == director || director.empty())
			listedPublishedFilms.push_back(films[k]);
}

std::vector<Film*> SystemInterface::getListedPublishedFilms() { return listedPublishedFilms; }

std::vector<Film*> SystemInterface::getListedSalableFilms() { return listedSalableFilms; }

std::vector<Film*> SystemInterface::getRecommendedFilms(int filmId)
{
	std::vector<Film*> relatedFilms = filmBox.findRelatedFilms(filmId);
	for (int k = 0; k < relatedFilms.size(); ++k)
		if (currentUser->alreadyHasBoughtFilm(relatedFilms[k]->getId()) || currentUser->getBalance() < relatedFilms[k]->getPrice())
			relatedFilms.erase(relatedFilms.begin() + k);
	return relatedFilms;
}