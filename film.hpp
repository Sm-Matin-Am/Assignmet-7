#ifndef FILM_HPP
#define FILM_HPP

#include "classes.hpp"
#include "customer.hpp"
// #include "publisher.hpp"
#include "comment.hpp"
#include <map>
#include <string>
#include <vector>

class Film
{
private:
	Publisher* publisher;
	std::string name;
	std::string director;
	std::string summary;
	int totalScore;
	double score;
	int id;
	int length;
	int year;
	int price;
	std::vector<Comment*> comments;
	std::map<int, int> userRatedFilm;
public:
	Film(Publisher* pub, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _id);
	std::string getName(void);
	std::string getDirector(void);
	std::string getSummary(void);
	Publisher* getPub(void);
	std::map<int, int>::iterator hasRatedBefore(int userId);
	int getYear(void);
	int getLength(void);
	int getId(void);
	int getPrice(void);
	int searchComment(int commentId);
	double getScore(void);
	double getFilmStatus(void);
	bool checkFilters(std::string _name, int _price, int min_year, int max_year, int min_rate, std::string _director);
	bool operator==(const Film*& f) const;
	void addScore(int userId, int _score);
	void edit(std::string argumentToChange, std::string newArgument);
	void editName(std::string newName);
	void editDirector(std::string newDirector);
	void editSummary(std::string newSummary);
	void editLength(int newLenght);
	void editYear(int newYear);
	void editPrice(int newPrice);
	void printInfo(void);
	void showDetails(void);
	void showComments(void);
	void deleteComment(int commentId);
	void addNewComment(std::string content, int _id, Customer* sender);
	void replay(int commentId, std::string replayContent, Customer* sender);
};

#endif