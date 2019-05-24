#include "customer.hpp"
#include "publisher.hpp"
#include "comment.hpp"
#include "message.hpp"
#include "exceptions.cpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include "constValues.hpp"

Film::Film(Publisher* pub, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _id)
	: publisher(pub)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
	totalScore = 0;
	score = 0;
}

 std::map<int, int>::iterator Film::hasRatedBefore(int userId)
{
	for (auto itr = userRatedFilm.begin(); itr != userRatedFilm.end(); ++itr)
		if (itr->first == userId)
			return itr;
	return userRatedFilm.end();
}

bool Film::operator==(const Film*& f) const
{
	if (id == f->id)
		return true;
	return false;
}

void Film::addScore(int userId, int _score)
{
	std::map<int, int>::iterator user = hasRatedBefore(userId);
	if (user != userRatedFilm.end())
		totalScore -= user->second;
	totalScore += _score;
	userRatedFilm.insert(std::pair<int, int>(userId, _score));
	score = (double) totalScore / userRatedFilm.size();
}



double Film::getScore(void) { return score; }

double Film::getFilmStatus(void)
{
	if (score >= 8) return STRONG;
	else if (score < 8 && score >= 5) return MEDIUM;
	else if (score < 5) return WEAK;
}

int Film::getId(void) { return id; }

int Film::getPrice(void) { return price; }

Publisher* Film::getPub(void) { return publisher; }

std::string Film::getName(void) { return name; }

int Film::getLength(void) { return length; }

std::string Film::getDirector(void) { return director; }

bool Film::checkFilters(std::string _name, int _price, int min_year, int max_year, int min_rate, std::string _director)
{
	if (!_name.empty() && _name != name)
		return false;
	if (_price != NO_PRICE_FILTER && _price != price)
		return false;
	if (year < min_year || year > max_year)
		return false;
	if (score < min_rate)
		return false;
	if (!_director.empty() && _director != director)
		return false;
	return true;
}

void Film::edit(std::string argumentToChange, std::string newArgument)
{
	if (argumentToChange == "name")
		this->editName(newArgument);
	else if (argumentToChange == "year")
		this->editYear(std::stoi(newArgument));
	else if (argumentToChange == "length")
		this->editLength(std::stoi(newArgument));
	else if (argumentToChange == "price")
		this->editPrice(std::stoi(newArgument));
	else if (argumentToChange == "summary")
		this->editSummary(newArgument);
	else if (argumentToChange == "director")
		this->editDirector(newArgument);
	else
		throw new BadRequest();
}

void Film::editName(std::string newName) { name = newName; }

void Film::editDirector(std::string newDirector) { director = newDirector; }

void Film::editSummary(std::string newSummary) { summary = newSummary; }

void Film::editLength(int newLenght) { length = newLenght; }

void Film::editYear(int newYear) { year = newYear; }

void Film::editPrice(int newPrice) { price = newPrice; }

void Film::setId(int _id) { id = _id; }

void Film::printInfo(void)
{
	std::cout << id << " | " << name << " | " << length << " | " << price << " | " << std::setprecision(2) << score << " | " << year << " | " << director << std::endl;
}

void Film::showDetails(void)
{
	std::cout << "Details of Film " << name << std::endl;
	std::cout << "Id = " << id << std::endl;
	std::cout << "Director = " << director << std::endl;
	std::cout << "Length = " << length << std::endl;
	std::cout << "Year = " << year << std::endl;
	std::cout << "Summary = " << summary << std::endl;
	std::cout << "Rate = " << std::setprecision(2) << score << std::endl;
	std::cout << "Price = " << price << std::endl;
	std::cout << "\n";
	
	this->showComments();
	std::cout << "\n";
}

void Film::showComments(void)
{
	std::cout << "Comments" << std::endl;
	for (int j = 0; j < comments.size(); ++j)
		comments[j]->print();
}

int Film::searchComment(int commentId)
{
	for (int k = 0; k < comments.size(); k++)
		if (comments[k]->getId() == commentId)
			return k;
	return -1;
}

void Film::deleteComment(int commentId)
{
	comments.erase(comments.begin() + searchComment(commentId));
}

void Film::addNewComment(std::string content, int _id, Customer* sender) 
{
	comments.push_back(new Comment(content, _id, sender));
}

void Film::replay(int commentId, std::string replayContent, Customer*  sender)
{
	Comment* targetComment = comments[this->searchComment(commentId)];
	targetComment->putReplay(new Comment(replayContent, targetComment->getId(), sender));
	std::string messageContent = "Publisher " + publisher->getUsername() + " with id " + std::to_string(publisher->getId()) + " reply to your comment.";
	Message* newMessage = new Message(messageContent);
	targetComment->getSender()->recieveMessage(newMessage);
}