#ifndef SYSTME_INTERFACE_HPP
#define SYSTME_INTERFACE_HPP

#include <vector>
#include <string>
#include "film.hpp"
#include "customer.hpp"
#include "idSeter.hpp"
#include "bank.hpp"
#include "commandDetails.hpp"
#include "filmRepository.hpp"
#include "constValues.hpp"

class SystemInterface
{
public:
	SystemInterface();
	Film* findFilmById(int id);
	std::vector<std::string> sortArguments(std::vector<std::string> neededArguments);
	std::vector<std::string>  handleSignupErrors(void);
	void analizeInput(std::string);
	void checkTitleOfCommand(std::string);
	void checkBodyOfCommand(std::string);
	void processInput(std::string inputCommand);
	void checkDuplicationOfUsername(std::string newUsername);
	void followPub(int id);
	void checkAccessibilityLevel(void);
	void processCommand(void);
	void processPostCommands(void);
	void processPutCommands(void);
	void processDeleteCommands(void);
	void processGetCommands(void);
	void signup(void);
	void login(void);
	void addFilm(void);
	void sellFilm(void);
	void putComment(void);
	void searchFilms(std::vector<Film*> films);
	void calcPortionOfSystem(Film* film);
	void rateFilm(void);
private:
	int money;
	std::vector<Customer*> registeredCustomers;
	Customer* currentUser;
	CommandDetails commandDetails;
	IdSeter* idManager;
	FilmRepository filmBox;
	Bank accounts;
};

#endif