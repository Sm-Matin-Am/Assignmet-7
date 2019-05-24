#include "publisher.hpp"
#include "customer.hpp"
#include "film.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>


Publisher::Publisher(std::string _email, std::string _username, std::string _password, int _age, int _id)
	: Customer(_email, _username, _password, _age, _id) {}

void Publisher::sendMessageTofollowers(void)
{
	std::string messageContent = "Publisher " + username + " with id " + std::to_string(id) + "register new film.";
	for (int i = 0; i < followers.size(); i++)
		this->sendMessage(followers[i], messageContent);
}

Film* Publisher::addFilm(std::vector<std::string> sortedArguments)
{
	Film* newFilm = new Film(this, sortedArguments[0], std::stoi(sortedArguments[1]), 
							 std::stoi(sortedArguments[2]), std::stoi(sortedArguments[3]), 
							 sortedArguments[4], sortedArguments[5], 
							 DEFAULT_ID);
	publishedFilms.push_back(newFilm);
	this->sendMessageTofollowers();
	return newFilm;
}

void Publisher::deleteComment(int filmId, int commentId)
{
	for (int j = 0; j < publishedFilms.size(); j++)
		if (publishedFilms[j]->getId() == filmId) {
			publishedFilms[j]->deleteComment(commentId);
			return;
		}
	throw new NotFound();
}

Film* Publisher::searchInPublishedFilms(int filmId)
{
	for (int k = 0; k < publishedFilms.size(); ++k)
		if (filmId == publishedFilms[k]->getId())
			return publishedFilms[k];
	throw new PermissionDenied();
}

std::vector<Film*> Publisher::getPublishedFilms(void) { return publishedFilms; }

void Publisher::editFilm(std::map<std::string, std::string> argumentsToChange) 
{
	Film* filmToEdit;
	for (auto itr = argumentsToChange.begin(); itr != argumentsToChange.end(); itr++)
		for (int j = 0; j < FILM_ARGUMENTS.size(); ++j) {
			if (itr->first == FILM_ARGUMENTS[j])
				filmToEdit->edit(itr->first, itr->second);
			else if (itr->first == "film_id")
				filmToEdit = this->searchInPublishedFilms(std::stoi(itr->second));
		}
}

void Publisher::deleteFilm(int id)
{
	for (int k = 0; k < publishedFilms.size(); ++k)
		if (id == publishedFilms[k]->getId()) {
			publishedFilms.erase(publishedFilms.begin() + k);
			return;
		}
	throw new PermissionDenied();
}

void Publisher::sortFollowers(void)
{
	Customer* temp;
	for (int k = 1; k < followers.size(); k++)
		if (followers[k]->getId() < followers[k - 1]->getId()) {
			temp = followers[k - 1];
			followers[k - 1] = followers[k];
			followers[k] = temp;
		}
}

void Publisher::showFollowers(void)
{
	std::cout << "List of Followers" << std::endl;
	std::cout << "#. User Id | User Username | User Email" << std::endl;
	for (int j = 0; j < followers.size(); j++)
		std::cout << j + 1 << ". " 
				  << followers[j]->getId() << " | " 
				  << followers[j]->getUsername() << " | " 
				  << followers[j]->getEmail() << std::endl;
}

void Publisher::addFollower(Customer* newFollower)
{
	followers.push_back(newFollower);
}

void Publisher::replayComment(int filmId, int commentId, std::string replayContent)
{
	for (int j = 0; j < publishedFilms.size(); j++)
		if (filmId == publishedFilms[j]->getId())
			publishedFilms[j]->replay(commentId, replayContent, this);
}