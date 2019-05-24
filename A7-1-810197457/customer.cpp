#include "customer.hpp"
// #include "publisher.hpp"
#include "film.hpp"
#include "message.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <string>
#include <vector>

bool Customer::operator==(const Customer*& c) const
{
	if (id == c->id)
		return true;
	return false;
}

Customer::Customer(std::string _email, std::string _username, std::string _password, int _age, int _id)
{
	id = _id;
	email = _email;
	username = _username;
	password = _password;
	age = _age;
	money = 0;
}

void Customer::deleteComment(int filmId, int commentId) { throw new PermissionDenied(); }

bool Customer::alreadyHasBoughtFilm(Film* film)
{
	for (int k = 0; k < purchasedFilms.size(); k++)
		if (purchasedFilms[k]->getId() == film->getId())
			return true;
	return false;
}

void Customer::showUnreadMessages(void)
{
	std::cout << "#. Notification Message" << std::endl;
	for (int j = inbox.size() - 1, i = 1; j >= 0; j--, i++) {
		if (inbox[j]->notRead())
			std::cout << i << ". " << inbox[j]->getText() << std::endl;
		inbox[j]->read();
	}
}

void Customer::showMessages(int limit)
{
	int k, i;
	std::cout << "#. Notification Message" << std::endl;
	for ((limit - inbox.size() > 0) ? k = inbox.size() : k = limit, i = 1; k >= 0; k--, i++)
		std::cout << i << ". " << inbox[k]->getText() << std::endl;
}

void Customer::increaseMoney(int amount) { money += amount; }

Film* Customer::searchInPublishedFilms(int filmId)
{
	throw new PermissionDenied();
}

Film* Customer::searchInPurchasedFilms(int filmId)
{
	for (int k = 0; k < purchasedFilms.size(); ++k)
		if (filmId == purchasedFilms[k]->getId())
			return purchasedFilms[k];
	throw new BadRequest();
}

bool Customer::checkLoginInfo(std::string _username, std::string _password)
{
	if (username == _username && password == _password)
		return true;
	return false;
}

std::string Customer::getEmail(void) { return email; }

std::string Customer::getUsername(void) { return username; }

int Customer::getId(void) { return id; }

Film* Customer::addFilm(std::vector<std::string> sortedArguments) { throw new PermissionDenied(); }

void Customer::editFilm(std::map<std::string, std::string> argumentsToChange) { throw new PermissionDenied(); }

void Customer::deleteFilm(int id) { throw new PermissionDenied(); }

void Customer::showFollowers(void) { throw new PermissionDenied(); }

void Customer::addFollower(Customer* newFollower) { throw new PermissionDenied(); }

void Customer::follow(Customer* pub)
{
	pub->addFollower(this);
	std::string messageContent = "User " + username + " with id " + std::to_string(id) + " follow you.";
	this->sendMessage(pub, messageContent);
}

void Customer::sendMessage(Customer* reciever, std::string messageContent)
{
	Message* newMessage = new Message(messageContent);
	reciever->recieveMessage(newMessage);
}

void Customer::recieveMessage(Message* newMessage) { inbox.push_back(newMessage); }

void Customer::buyFilm(Film* film) 
{
	if (money < film->getPrice())
		throw new PermissionDenied();
	money -= film->getPrice();
	purchasedFilms.push_back(film); 
}

std::vector<Film*> Customer::getPublishedFilms(void) { throw new PermissionDenied(); }

std::vector<Film*> Customer::getPurchasedFilms(void) { return purchasedFilms; }

void Customer::replayComment(int filmId, int commentId, std::string replayContent) { throw new PermissionDenied(); }