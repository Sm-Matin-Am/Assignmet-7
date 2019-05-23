#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

#define POST "POST"
#define PUT "PUT"
#define DELETE "DELETE"
#define GET "GET"
#define ARG_NOT_FOUND ""
#define STRONG 0.95
#define MEDIUM 0.9
#define WEAK 0.8
#define PUB_REPLAY 'P'
#define FILM_REGISTERATION 'R'
#define FOLLOW 'F'
#define BUY 'B'
#define RATE 'S'
#define COMMENT 'C'
#define DEFAULT_ID 0
#define NO_LIMIT -1
#define NO_PRICE_FILTER -1
#define UNREAD false

const std::vector<std::string> CORRECT_COMMAND_TITLES = { POST, PUT, DELETE, GET }; 
const std::vector<std::string> CORRECT_COMMAND_BODIES = { "signup", "login", "films", "money", 
														"replies", "followers", "buy", "rate", 
														"comments", "published", "purchased", 
														"notifications",  "notifications read" };
const std::vector<std::string> SIGNUP_ARGUMENTS = { "email", "username", "password", "age", "publisher" };
const std::vector<std::string> FILM_ARGUMENTS = { "name", "year", "length" , "price", "summary", "director" };
const std::vector<std::string> SEARCH_FIELDS = { "name", "price", "min_year", "max_year", "min_rate", "director" };
const std::vector<std::string> LOGIN_ARGUMENTS = { "username", "password" };
const std::vector<std::string> REPLAY_ARGUMENTS = { "film_id", "comment_id", "content" };
const std::vector<std::string> RATE_ARGUMENTS = { "film_id", "score" };
const std::vector<std::string> COMMENT_ARGUMENTS = { "film_id", "content" };
const std::vector<std::string> BLANK_FIELDS = { "", std::to_string(NO_PRICE_FILTER), "0", "10000", "0", "" };

std::string getArgument(std::string arg, std::map<std::string, std::string> map)
{
	for (auto itr = map.begin(); itr != map.end(); ++itr)
		if (arg == itr->first)
			return itr->second;
	return ARG_NOT_FOUND;
}

class IdSeter
{
private:
	int maxFilmId;
	int maxCommentId;
	int maxUserId;
public:
	IdSeter();
	int makeNewFilmId(void);
	int makeNewUserId(void);
	int makeNewCommentId(void);
	// void decFilmId(void);
};

IdSeter::IdSeter(void)
{
	maxFilmId = 0;
	maxCommentId = 0;
	maxUserId = 0;
}

int IdSeter::makeNewCommentId(void) { return ++maxCommentId; }

int IdSeter::makeNewUserId(void) { return ++maxUserId; }

int IdSeter::makeNewFilmId(void) { return ++maxFilmId; }
// void IdSeter::decFilmId(void) { maxFilmId--; }

std::string deleteWhiteSpacesAtBegin(std::string& input)
{
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ')
			return input;
		input.erase(input.begin());
	}
}
std::string deleteWhiteSpacesAtEnd(std::string input)
{
	for (int j = input.size(); j >= 0; j--) {
		if (input[j] != ' ')
			return input;
		input.erase(input.end() - 1);
	}
}

class BadRequest : public std::exception 
{
public:
	const char* what() const noexcept { return "Bad Request"; }
};

class NotFound : public std::exception 
{
public:
	const char* what() const noexcept { return "Not Found"; }
};

class PermissionDenied : public std::exception 
{
public:
	const char* what() const noexcept { return "Permission Denied"; }
};

class CommandDetails
{
public:
	std::string title;
	std::string command;
	std::map<std::string, std::string> arguments;
	void clear();
};

void CommandDetails::clear(void)
{
	title.clear();
	command.clear();
	arguments.clear();
}

class Message
{
public:
	Message(std::string _content);
	// Message(char type, std::string name, int id);
	std::string getText(void);
	bool notRead(void);
	void read(void);
protected:////////////////////////////////////////////////////////////////////////////////
	std::string content;
	bool readFlag;
};

Message::Message(std::string _content) 
{ 
	content = _content; 
	readFlag = false;
}

std::string Message::getText(void) { return content; }

bool Message::notRead(void) { return !readFlag; }

void Message::read(void) { readFlag = true; }

class Comment
{
private:
	int id;
	std::string commentText;
	// std::map<int, Comment*> replay;
	std::vector<Comment*> replies;
public:
	Comment(std::string _content, int _id);
	int getId(void);
	void putReplay(Comment* replay);
	void print(void);
};

Comment::Comment(std::string _content, int _id)
{
	commentText = _content;
	id = _id;
}

void Comment::putReplay(Comment* replay) { replies.push_back(replay); }

void Comment::print(void)
{
	std::cout << id << " " << commentText << std::endl;
	for (int i = 0; i < replies.size(); i++) {
		std::cout << i + 1 << ". ";
		replies[i]->print();
	}
}

int Comment::getId(void) { return id; }

class Publisher;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	Publisher* getPub(void);
	std::map<int, int>::iterator hasRatedBefore(int userId);
	// Comment* searchComment(int CommentId);
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
	void setId(int _id);
	void editPrice(int newPrice);
	void printInfo(void);
	void showDetails(void);
	void showComments(void);
	void deleteComment(int commentId);
	void addNewComment(std::string content, int _id);
	void replay(int commentId, std::string replayContent);
};

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

bool Film::operator==(const Film*& f) const//***************************************************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
{
	if (id == f->id)
		return true;
	return false;
}

void Film::addScore(int userId, int _score)
{
	std::map<int, int>::iterator user = hasRatedBefore(userId);
	if (user == userRatedFilm.end())
		totalScore -= user->second;
	totalScore += _score;
	score = (double) totalScore / userRatedFilm.size();
}

void Film::replay(int commentId, std::string replayContent)
{
	Comment* targetComment = comments[this->searchComment(commentId)];
	targetComment->putReplay(new Comment(replayContent, targetComment->getId()));
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
	std::cout << "Rate = " << std::setprecision(2) << score << std::endl; //?????????????????????????????????????????????????????????????????????????????????????????????????????????
	std::cout << "Price = " << price << std::endl;
	std::cout << "\n";
	
	this->showComments();
	std::cout << "\n";
}

void Film::showComments(void)
{
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

void Film::deleteComment(int commentNum)
{
	comments.erase(comments.begin() + commentNum);
}

void Film::addNewComment(std::string content, int _id) 
{
	comments.push_back(new Comment(content, _id));
}

// class Customer;////////////////////////////////////////////////////////////////////////////////////////////////////
class Customer
{
protected://////////////////////////////////////////////////////////////////////////////
	std::string email;
	std::string username;
	std::string password;
	int id; // id is int or string ???????????????????????????????????????????????????
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
	void follow(Customer* pub);//////////////////////////////////////////////////////////////////////////publisher* or customer*
	void sendMessage(Customer* reciever, std::string messageContent);
	void recieveMessage(Message* newMessage);
	void buyFilm(Film* film);
	void increaseMoney(int amount);
	void showMessages(void);
	void showUnreadMessages(int limit);
//	void putComment(Film* film, std::string commentText, int _id);
	std::string getEmail(void);
	std::string getUsername(void);
	std::vector<Film*> getPurchasedFilms(void);
	Film* searchInPurchasedFilms(int filmId);
	virtual void deleteComment(int id);
	virtual std::vector<Film*> getPublishedFilms(void);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumentsToChange);
	virtual Film* addFilm(std::vector<std::string> sortedArguments);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
	virtual void replayComment(int filmId, int commentId, std::string replayContent);
};

bool Customer::operator==(const Customer*& c) const//************************************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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

void Customer::deleteComment(int id) { throw new PermissionDenied(); }

bool Customer::alreadyHasBoughtFilm(Film* film)
{
	for (int k = 0; k < purchasedFilms.size(); k++)
		if (purchasedFilms[k] == film)
			return true;
	return false;
}

void Customer::showMessages(void)
{
	for (int j = inbox.size() - 1; j >= 0; j--) {
		std::cout << inbox.size() - j << ". " << inbox[j]->getText() << std::endl;
		inbox[j]->read();
	}
}

void Customer::showUnreadMessages(int limit)
{
	// for (int k = 0; k < inbox.size() && k < limit; k++)
	// 	if (inbox[k]->notRead())
	// 		cout << k + 1 << ". " << inbox[k]->getText() << std::endl;
	int k;
	for ((limit - inbox.size() > 0) ? k = inbox.size() : k = limit; k >= 0; k--)
		if (inbox[k]->notRead())
			std::cout << k + 1 << ". " << inbox[k]->getText() << std::endl;
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
	// std::string messageContent = "User " + username + " with id " + std::to_string(id) + " buy your film " + film->getName() + "with id " + std::to_string(film->getId()) + ".";
	// this->sendMessage(film->getPub(), messageContent);//************ to whom?????????????????????????/
}

std::vector<Film*> Customer::getPublishedFilms(void) { throw new PermissionDenied(); }

std::vector<Film*> Customer::getPurchasedFilms(void) { return purchasedFilms; }

// void Customer::putComment(Film* film, std::string commentText, int _id)
// {
	// int filmId;
	// Film* film = findFilmById(std::stoi(info.begin()->second));
	// film->addNewComment(commentText, _id);
	// std::string messageContent = "User " + username + " with id " + std::to_string(id) + " comment on your film " + film->getName() + " with id " + std::to_string(film->getId());
	// this->sendMessage(film->getPub(), messageContent);
	// Message* newMessage = new Message(messageContent);
	// film->getPub()->recieveMessage(newMessage);
// }

void Customer::replayComment(int filmId, int commentId, std::string replayContent) { throw new PermissionDenied(); }

class Publisher : public Customer
{
private:
	std::vector<Customer*> followers;
	std::vector<Film*> publishedFilms;
public:
	Publisher(std::string _email, std::string _username, std::string _password, int _age, int _id);
	void sortFollowers(void);
	void sendMessageTofollowers(void);
	virtual std::vector<Film*> getPublishedFilms(void);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual void deleteComment(int id);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumentsToChange);
	virtual Film* addFilm(std::vector<std::string> sortedArguments);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
	virtual void replayComment(int filmId, int commentId, std::string replayContent);
};

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

void Publisher::deleteComment(int id)
{
	for (int j = 0; j < publishedFilms.size(); j++)
		if (int num = publishedFilms[j]->searchComment(id) != -1) {//??????????????????????????????????????????????????
			publishedFilms[j]->deleteComment(num);
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
			// else????????????????????????????????????????????????????????????????????????????????????????????????????///
				// throw new BadRequest();
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
			publishedFilms[j]->replay(commentId, replayContent);
}

Customer* NO_USER = new Customer("-", "-", "-", 0, 0);

class FilmRepository
{
private:
	std::vector<Film*> films;
	std::vector<Film*> topFilms;
public:
	void addFilm(Film* film);
	void deleteFilm(int id);
	void findTopFilms(void);
	void showTopFilms(Customer* user);
	Film* chooseOlder(int& indexOfBestFilm, int k, std::vector<Film*> allFilms);
	std::vector<Film*> getFilms(void);
};

void FilmRepository::addFilm(Film* film) { films.push_back(film); }

void FilmRepository::deleteFilm(int id)
{
	for (int i = 0; i < films.size(); i++)
		if (films[i]->getId() == id) {
			films.erase(films.begin() + i);
			break;
		}
}

Film* FilmRepository::chooseOlder(int& indexOfBestFilm, int k, std::vector<Film*> allFilms)
{
	if (indexOfBestFilm > k) {
//		allFilms[indexOfBestFilm] = allFilms[k];
		indexOfBestFilm = k;
	}
	return allFilms[indexOfBestFilm];
}

void FilmRepository::findTopFilms(void)
{
	std::vector<Film*> allFilms = films;
	int indexOfBestFilm = 0;
	Film* Bestfilm;
	for (int i = 0; i < films.size(); ++i) {
		Bestfilm = allFilms[0];
		for (int k = 1; k < allFilms.size(); k++) {
			if (allFilms[k]->getScore() > Bestfilm->getScore()) {
				Bestfilm = allFilms[k];
				indexOfBestFilm = k;
			}
			else if (allFilms[k]->getScore() == Bestfilm->getScore())
				Bestfilm = this->chooseOlder(indexOfBestFilm, k, allFilms);
		}
		// topFilms[i] = Bestfilm;
		topFilms.push_back(Bestfilm);
		allFilms.erase(allFilms.begin() + indexOfBestFilm);
		indexOfBestFilm = 0;
	}
}

void FilmRepository::showTopFilms(Customer* user)
{
	this->findTopFilms();
	for (int i = 0; i < topFilms.size(); ++i)
		if (user->alreadyHasBoughtFilm(topFilms[i]))
			topFilms.erase(topFilms.begin() + i);
	std::cout << "#. Film Id | Film Name | Film Lenght | Film Director" << std::endl;
	for (int j = 0; j < 4 && j < topFilms.size(); j++)
		std::cout << j + 1 << ". " << topFilms[j]->getId()
				  << " | " << topFilms[j]->getName()
				  << " | " << topFilms[j]->getLength() 
				  <<  " | " << topFilms[j]->getDirector()
				  << std::endl;
}

std::vector<Film*> search(std::vector<Film*> films, std::string name = "", int price = NO_PRICE_FILTER, 
										  int min_year = 0, int max_year = 10000, 
										  int min_rate = 0, std::string director = "")
{
	std::vector<Film*> searchResault = films;
	for (int i = 0; i < films.size(); i++)
		if (!films[i]->checkFilters(name, price, min_year, max_year, min_rate, director))//??????????????????????????????????????????????????????????????????
			searchResault.erase(searchResault.begin() + i);
	return searchResault;
}

std::vector<Film*> FilmRepository::getFilms(void) { return films; }

class Bank
{
private:
	std::map<int, int> assets;
public:
	void addAccount(int id);
	void deposite(int id, int money);
	int withdraw(int id);
	std::map<int, int>::iterator searchAccount(int id);
};

void Bank::addAccount(int id)
{
	assets.insert(std::pair<int, double> (id, 0));
}

void Bank::deposite(int id, int money)
{
	searchAccount(id)->second += money;
}
	
int Bank::withdraw(int id)
{
	int withdrawalMoney = searchAccount(id)->second;
	searchAccount(id)->second = 0;
	return withdrawalMoney;
}
	
std::map<int, int>::iterator Bank::searchAccount(int id)
{
	for (auto itr = assets.begin(); itr != assets.end(); itr++)
		if (itr->first == id)
			return itr;
	throw new NotFound();
}

class SystemInterface
{
public:
	SystemInterface();
	Film* findFilmById(int id);
	std::vector<std::string> sortArguments(std::vector<std::string> neededArguments);
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
	std::vector<std::string>  handleSignupErrors(void);
	void sellFilm(void);
	void putComment(void);
	void searchFilms(std::vector<Film*> films);
	void calcPortionOfSystem(Film* film);
private:
	int money;
	std::vector<Customer*> registeredCustomers;
	Customer* currentUser;
	CommandDetails commandDetails;
	IdSeter* idManager;
	FilmRepository filmBox;
	Bank accounts;
};

SystemInterface::SystemInterface(void)
	: currentUser(NO_USER)
{
	idManager = new IdSeter();
	money = 0;
}

void SystemInterface::processInput(std::string inputCommand)
{
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
	else if (commandText == "rate") {
		std::vector<std::string> sortedArguments = this->sortArguments(RATE_ARGUMENTS);
		findFilmById(std::stoi(sortedArguments[0]))->addScore(currentUser->getId(), std::stoi(sortedArguments[1]));
	}
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
		std::cout << "OK" << std::endl;
	}
	else if (commandDetails.command == "comments")
		currentUser->deleteComment(std::stoi(commandDetails.arguments.begin()->second));
	else
		throw new NotFound();
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
		currentUser->showUnreadMessages(std::stoi(commandDetails.arguments.begin()->second));
	else if (commandDetails.command == "notifications read")
		currentUser->showMessages();
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
}

void SystemInterface::putComment(void)
{
	std::vector<std::string> sortedArguments = this->sortArguments(COMMENT_ARGUMENTS);
	Film* film = findFilmById(std::stoi(sortedArguments[0]));
	// currentUser->putComment(film, sortedArguments[1], idManager->makeNewCommentId());
	film->addNewComment(sortedArguments[1], idManager->makeNewCommentId());
	std::string messageContent = "User " + currentUser->getUsername() + " with id " + std::to_string(currentUser->getId()) + " comment on your film " + film->getName() + " with id " + std::to_string(film->getId());
	Message* newMessage = new Message(messageContent);
	film->getPub()->recieveMessage(newMessage);
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
	accounts.addAccount(userId);///////////////////////////************************************************************
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

void findArgument(std::vector<std::string> listOfArgs, std::map<std::string, std::string>::iterator arg, 
															  std::vector<std::string>& sortedArguments)
{
	for (int i = 0; i < listOfArgs.size(); ++i)
		if (listOfArgs[i] == arg->first) {
			sortedArguments[i] = arg->second;
			return;
		}
	if (arg->first != "Publisher")
		throw new BadRequest();//???????????not found?????????????????????????????????????????????????????????????????????????
	return;
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

std::string readLine(int& foundCharPlace, std::string inputLine, int previousPlace)
{
	std::string separatedPiece;
	foundCharPlace = inputLine.find_first_of(' ', foundCharPlace + 1);
	separatedPiece = inputLine.substr(previousPlace + 1, foundCharPlace - previousPlace - 1);
	if (separatedPiece == "notifications")
		separatedPiece += readLine(foundCharPlace, inputLine, foundCharPlace);
	return separatedPiece;
}

std::vector<std::string> separateInput(std::string inputLine)
{
	std::vector<std::string> separatedCommand;
	std::string separatedPiece;
	int foundCharPlace = 0, previousPlace = -1;
	
	while (foundCharPlace != -1)
	{
		separatedPiece = readLine(foundCharPlace, inputLine, previousPlace);

		if (separatedPiece != "?")
			separatedCommand.push_back(separatedPiece);

		previousPlace = foundCharPlace;
	}
	return separatedCommand;
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

int main()
{
	SystemInterface si;
	std::string inputCommand;

	while (getline(std::cin, inputCommand))
			si.processInput(deleteWhiteSpacesAtEnd(deleteWhiteSpacesAtBegin(inputCommand)));
}
