#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "classes.hpp"
#include "film.hpp"
#include "message.hpp"
#include <map>
#include <string>
#include <vector>

class Customer
{
protected:
	std::string email;
	std::string username;
	std::string password;
	int id;
	int age;
	int money;
	std::vector<Film*> purchasedFilms;
	std::vector<Message*> inbox;
public:
	Customer(std::string _email, std::string _username, std::string _password, int _age, int _id);
	int getId(void);
	bool operator==(const Customer*& C) const;
	bool checkLoginInfo(std::string _username, std::string _password);
	bool alreadyHasBoughtFilm(Film* film);
	void follow(Customer* pub);
	void sendMessage(Customer* reciever, std::string messageContent);
	void recieveMessage(Message* newMessage);
	void buyFilm(Film* film);
	void increaseMoney(int amount);
	void showMessages(int limit);
	void showUnreadMessages(void);
	std::string getEmail(void);
	std::string getUsername(void);
	std::vector<Film*> getPurchasedFilms(void);
	Film* searchInPurchasedFilms(int filmId);
	virtual std::vector<Film*> getPublishedFilms(void);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual Film* addFilm(std::vector<std::string> sortedArguments);
	virtual void deleteComment(int filmId, int commentId);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumentsToChange);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
	virtual void replayComment(int filmId, int commentId, std::string replayContent);
};

#endif