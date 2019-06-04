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
	Customer* findUserById(int id);
	std::vector<std::string> sortArguments(std::vector<std::string> neededArguments);
	std::vector<Film*> getListedPublishedFilms();
	std::vector<Film*> getListedSalableFilms();
	std::vector<Film*> getRecommendedFilms(int filmId);
	void setSalableFilms(int budget, std::string director);
	void setPublishedFilms(std::vector<Film*> films, std::string director);
	void handleSignupErrors(std::string email, std::string username, std::string password, std::string age);
	int findPostCommand(void);
	void checkIfSystemIsFree(void);
	void analizeInput(std::string);
	void checkTitleOfCommand(std::string);
	void checkBodyOfCommand(std::string);
	void processInput(std::string inputCommand);
	void checkDuplicationOfUsername(std::string newUsername);
	void followPub(int id);
	void checkAccessibilityLevel(void);
	void processCommand(void);
	void processPostCommands(void);
	void processGetCommands(void);
	int signup(std::string email, std::string username, std::string password, std::string age, std::string accountType);
	int login(std::string username, std::string password);
	void addFilm(std::string name, std::string year, std::string length, 
							  std::string price, std::string summary, std::string director);
	void removeFilm(int filmId);
	void sellFilm(int filmId);
	void putComment(void);
	void searchFilms(std::vector<Film*> films);
	void calcPortionOfSystem(Film* film);
	void rateFilm(int filmId, int score);
	void logout(void);
	void searchFilms(std::vector<Film*> films, std::string director);
private:
	int money;
	std::vector<Film*> listedPublishedFilms;
	std::vector<Film*> listedSalableFilms;
	std::vector<Customer*> registeredCustomers;
	Customer* currentUser;
	CommandDetails commandDetails;
	IdSeter* idManager;
	FilmRepository filmBox;
	Bank accounts;
};

#endif