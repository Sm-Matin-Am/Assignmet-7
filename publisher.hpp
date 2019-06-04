#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include "classes.hpp"
#include "customer.hpp"
#include "searchArguments.hpp"
#include "constValues.hpp"
#include "film.hpp"
#include <string>
#include <vector>
#include <map>

class Publisher : public Customer
{
private:
	std::vector<Customer*> followers;
	std::vector<Film*> publishedFilms;
public:
	Publisher(std::string _email, std::string _username, std::string _password, int _age, int _id);
	void sortFollowers(void);
	void sendMessageTofollowers(void);
	virtual bool isPublisher();
	virtual Film* addFilm(std::string name, std::string year, std::string length, 
							  std::string price, std::string summary, std::string director, int _id);
	virtual std::vector<Film*> getPublishedFilms(void);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual void deleteComment(int filmId, int commentId);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumentsToChange);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
	virtual void replayComment(int filmId, int commentId, std::string replayContent);
};

#endif