#include <iostream>
#include <string>
#include <vector>
#include <map>

#define POST "POST"
#define PUT "PUT"
#define DELETE "DELETE"
#define GET "GET"
#define ARG_NOT_FOUND ""
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
const std::vector<std::string> SERACH_FIELDS = { "name", "price", "min_year", "max_year", "min_rate", "director" };

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
	void decFilmId(void);
};

IdSeter::IdSeter(void)
{
	maxFilmId = 0;
	maxCommentId = 0;
	maxUserId = 0;
}

int IdSeter::makeNewCommentId(void) { return maxCommentId++; }
int IdSeter::makeNewUserId(void) { return maxUserId++; }
int IdSeter::makeNewFilmId(void) { return maxFilmId++; }
void decFilmId(void) { maxFilmId--; }

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
	// std::string getText(void);
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

// std::string Message::getText(void) { return content; }

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
	void putReplay(Comment* replay);
	void print(void);
};

Comment::Comment(std::string _content, int _id)
{
	commandText = _content;
	id = _id;
}

void Comment::putReplay(Comment* replay) { replies.push_back(replay); }

void Comment::print(void)
{
	std::cout << id << " " << content << std::endl;
	for (int i = 0; i < replies.size(); i++)
		std::cout << i + 1 << ". " << replies[i]->print();
}

class Film
{
private:
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
public:
	Film(std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _id);
	std::string getName(void);
	std::string getLength(void);
	std::string getDirector(void);
	bool checkFilters(std::string _name, int _price, int min_year, int max_year, int min_rate, std::string _director);
	int getId(void);
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
};

Film::Film(std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _id)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
}

int Film::getId(void) { return id; }

std::string Film::getName(void) { return name; }

std::string getLength(void) { return length; }

std::string getDirector(void) { return director; }

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
	if (!director.empty() && _director != director)
		return false;
	return true;
}

void Film::edit(std::string argumentToChange, std::string newArgument)
{
	if (argumentToChange == "name")
		this->editName(newArgument);
	else if (argumentToChange == "year")
		this->editYear(stoi(newArgument));
	else if (argumentToChange == "length")
		this->editLength(stoi(newArgument));
	else if (argumentToChange == "price")
		this->editPrice(stoi(newArgument));
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
	std::cout << id << " | " << name << " | " << length << " | " << price << " | " << std::setprecision(2) << score << year << " | " <<  director << std::endl;
}

void Film::showDetails(void)
{
	std::cout << "Id = " << id << std::endl <<
	std::cout << "Director = " << director << std::endl <<
	std::cout << "Length = " << length << std::endl <<
	std::cout << "Year = " << year << std::endl <<
	std::cout << "Summary = " << summary << std::endl <<
	std::cout << "Rate = " << std::setprecision(2) << score << std::endl << //?????????????????????????????????????????????????????????????????????????????????????????????????????????
	std::cout << "Price = " << price << std::endl;

	this->showComments();
	std::cout << "\n";
}

void Film::showComments(void)
{
	for (int j = 0; j < comments.size(); ++j)
		comments[j]->print();
}

class FilmRepository
{
private:
	// std::map<int, Film*> films;
	std::vector<Film*> films;
	std::vector<Film*> topFilms; // (4)
public:
	void addFilm(Film* film);
	// void edit if once I changed it in publisher map it may dont need to be changed here again
	void deleteFilm(int id);
	void findTopFilms(void);
	void showTopFilms(void);
	Film* chooseOlder(int& indexOfBestFilm, int k, std::vector<Film*> allFilms);
	std::vector<Film*> search(std::string name = "", int price = NO_PRICE_FILTER, 
										  int min_year = 0, int max_year = 10000, 
										  int min_rate = 0, std::string director = "");
};

void FilmRepository::addFilm(Film* film)
{
	// films.insert(std::pair<int, Film*>(id, film));
	films.push_back(newFilm);
}

void FilmRepository::deleteFilm(int id)
{
	for (int i = 0; i < films.size(); i++)
		if (films[i].getId == id) {
			films.erase(films.begin() + i);
			break;
		}
}

Film* FilmRepository::chooseOlder(int& indexOfBestFilm, int k, std::vector<Film*> allFilms)
{
	if (indexOfBestFilm < k) {
		allFilms[indexOfBestFilm] = allFilms[k];
		indexOfBestFilm = k;
	}
	return allFilms[indexOfBestFilm];
}

void FilmRepository::findTopFilms(void)
{
	std::vector<Film*> allFilms = films;
	int indexOfBestFilm = 0;
	Film* Bestfilm = allFilms[indexOfBestFilm];
	for (int i = 0; i < film.size(); ++i) {
		for (int k = 1, i = 0; k < allFilms.size() && i < 4; k++, i++) {
			if (allFilms[k] > Bestfilm) {
				Bestfilm = allFilms[k];
				indexOfBestFilm = k;
			}
			else if (allFilms[k] == Bestfilm)
				Bestfilm = this->chooseOlder(indexOfBestFilm, k, allFilms);
		}
		// topFilms[i] = Bestfilm;
		topFilms.push_back(Bestfilm);
		allFilms.erase(allFilms.begin() + indexOfBestFilm);
	}
}

void FilmRepository::showTopFilms(void)
{
	this->findTopFilms();
	std::cout << "#. Film Id | Film Name | Film Lenght | Film Director" << std::endl;
	for (int j = 0; j < topFilms.size(); j++)
		std::cout << j + 1 << ". " << topFilms[j]->getId()
				  << " | " << topFilms[j]->getName()
				  << " | " << topFilms[j]->getLength() 
				  <<  " | " << topFilms[j]->getDirector()
				  << std::endl;
}

std::vector<Film*> FilmRepository::search(std::string name = "", int price = NO_PRICE_FILTER, 
										  int min_year = 0, int max_year = 10000, 
										  int min_rate = 0, std::string director = "")
{
	std::vector<Film*> searchResault = films;
	for (int i = 0; i < films.size(); i++)
		if (!films[i]->checkFilters(name, price, min_year, max_year, min_rate, director))//??????????????????????????????????????????????????????????????????
			searchResault.erase(searchResault.begin() + i);
	return searchResault;
}

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
	bool operator==(const Customer& C) const;
	bool checkLoginInfo(std::string _username, std::string _password);
	void follow(Customer* pub);//////////////////////////////////////////////////////////////////////////publisher* or customer*
	void sendMessage(Customer* reciever, std::string messageContent);
	void recieveMessage(Message* newMessage);
	void buyFilm(Film* film);
	void increaseMoney(int amount);
	void showMessages(void);
	void showUnreadMessages(int limit);
	std::string getEmail(void);
	std::string getUsername(void);
	Film* searchInPurchasedFilms(int filmId);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumantsToChange);
	virtual void addFilm(Film* newFilm);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
	virtual void replayCommand()
};

bool Customer::operator==(const Customer& c) const
{
	if (id == c.id)
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
}

void Customer::showMessages(void)
{
	for (int j = 0; j < inbox.size(); j++) {
		cout << j + 1 << ". " << inbox[j]->getText() << std::endl;
		Message->read();
	}
}

void Customer::showUnreadMessages(int limit)
{
	for (int k = 0; k < inbox.size() && k < limit; k++)
		if (inbox[k]->notRead())
			cout << j + 1 << ". " << inbox[j]->getText() << std::endl;
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
	throw new BadRequest();
}

std::string Customer::getEmail(void) { return email; }

std::string Customer::getUsername(void) { return username; }

void Customer::getId(void) { return id; }

void Customer::addFilm(Film* newFilm)
{
	delete newFilm;
	throw new PermissionDenied();
}

void Customer::editFilm(std::map<std::string, std::string> argumantsToChange) { throw new PermissionDenied(); }

void Customer::deleteFilm(int id) { throw new PermissionDenied(); }

void Customer::showFollowers(void) { throw new PermissionDenied(); }

void Customer::addFollower(Customer* newFollower) { throw new PermissionDenied(); }

void Customer::follow(Customer* pub)
{
	pub->addFollower(this);
	std::string messageContent = "User " + name + " with id " + id + " follow you." << std::endl;
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
	purchasedFilms.push_back(film); 
	std::string messageContent = "User " + name + " with id " + id + " buy your film " + film->getName() + "with id " + film->getId() + ".";
	this->sendMessage(, messageContent);//************ to whom?????????????????????????/
}

class Publisher : public Customer
{
private:
	std::vector<Customer*> followers;
	std::vector<Film*> publishedFilms;
public:
	Publisher(std::string _email, std::string _username, std::string _password, int _age, int _id);
	void sortFollowers(void);
	void sendMessageTofollowers(void);
	virtual Film* searchInPublishedFilms(int filmId);
	virtual void addFollower(Customer* newFollower);
	virtual void editFilm(std::map<std::string, std::string> argumantsToChange);
	virtual void addFilm(Film* newFilm);
	virtual void deleteFilm(int id);
	virtual void showFollowers(void);
};

Publisher::Publisher(std::string _email, std::string _username, std::string _password, int _age, int _id)
	: Customer(_email, _username, _password, _age, _id) {}

void Publisher::addFilm(Film* newFilm)
{
	publishedFilms.push_back(newFilm);
	// this->sendMessageTofollowers();????????????????????????????????????????????????????????????????????
}

Film* Publisher::searchInPublishedFilms(int filmId)
{
	for (int k = 0; k < publishedFilms.size(); ++k)
		if (filmId == publishedFilms[k]->getId())
			return publishedFilms[k];
	throw new PermissionDenied();
}
void Publisher::editFilm(std::map<std::string, std::string> argumantsToChange) 
{
	Film* filmToEdit;
	for (auto itr = argumantsToChange.begin(); itr != argumantsToChange.end(); itr++) {
		if (itr->first == FILM_ARGUMENTS[j])
			filmToEdit->edit(itr->first, itr->second);
		else if (itr->first == "film_id")
			filmToEdit = this->searchInPublishedFilms(stoi(itr->second));
		else
			throw new BadRequest();
	}
}

void Publisher::deleteFilm(int Id)
{
	for (int k = 0; k < publishedFilms.size(); ++k)
		if (filmId == publishedFilms[k]->getId()) {
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
	std::cout << "#. User Id | User Username | User Email" << endl;
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

Customer* NO_USER = new Customer("-", "-", "-", 0, 0);

class SystemInterface
{
public:
	SystemInterface();
	Film* findFilmById(int id);
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
	void handleSignupErrors(void);
	// void sellFilm(int filmId);
	void searchFilms(void);
private:
	int money;
	// std::map<int, Customer*> registeredCustomers;
	std::vector<Customer*> registeredCustomers;
	Customer* currentUser;
	CommandDetails commandDetails;
	IdSeter* idManager;
	FilmRepository* filmBox;
};

SystemInterface::SystemInterface(void)
	: currentUser(NO_USER)
{
	idManager = new IdSeter();
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
//	std::cout << "OK" << std::endl;
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
			this->processPostCommands(commandDetails);
	else if (commandDetails.title == PUT)
			this->processPutCommands(commandDetails);
	else if (commandDetails.title == DELETE)
			this->processDeleteCommands(commandDetails);
	else if (commandDetails.title == GET)
			this->processGetCommands(commandDetails);
}

void SystemInterface::processPostCommands(void)
{
	std::string commandText = commandDetails.command;
	if (commandText == "signup")
		this->signup();
	else if (commandText == "login")
		this->login();
	else if (commandText == "films") {
		this->addFilm();
	}
	else if (commandText == "money") {
		if (commandDetails.arguments.empty())
		else
			currentUser->increaseMoney(stoi(commandDetails.argumants.begin()->second));
	}
	else if (commandText == "replies")
	else if (commandText == "followers")
		this->follow(stoi(commandDetails.arguments.begin()->second));//*******************************currentUser or this
	else if (commandText == "buy")
		currentUser->buyFilm(this->findFilmById(commandDetails.argumants.begin()->second));
		// this->sellFilm(commandDetails.argumants.begin()->second);
	else if (commandText == "rate")
	else if (commandText == "comments")
	else
		throw new NotFound();
}
	void SystemInterface::processPutCommands(void)
	{
		if (commandDetails.command == "films")
			currentUser->editFilm(commandDetails.arguments);
		else
			throw new NotFound();
	}
	void SystemInterface::processDeleteCommands(void)
	{
		if (commandDetails.command == "films") {
			this->findFilmById(stoi(commandDetails.arguments.begin()->second));
			currentUser->deleteFilm(stoi(commandDetails.arguments.begin()->second));
			filmBox.deleteFilm(stoi(commandDetails.arguments.begin()->second));
		}
		else if (commandDetails.command == "comments")
		else
			throw new NotFound();
	}
	void SystemInterface::processGetCommands(void)
	{
		if (commandDetails.command == "followers")
			currentUser->showFollowers();
		else if (commandDetails.command == "published")
		else if (commandDetails.command == "films")
			this->searchFilms();
		else if (commandDetails.command == "purchased")
		else if (commandDetails.command == "notifications")
			currentUser->showMessages();
		else if (commandDetails.command == "notifications read")
			currentUser->showMessages(stoi(commandDetails.argumants.begin()->second));
		else
			throw new NotFound();
	}

void SystemInterface::searchFilms(void)
{
	if (commandDetails.arguments.begin()->first == "film_id") {
		findFilmById(commandDetails.arguments.begin()->second)->showDetails();
		filmBox->showTopFilms();
	}
	else
	{//ddddddddddddddddddduuuuuuuuuuuuuuuuuuuuuuppppppppppppppppppppllllllllllllllllllliiiiiiiiiiiiiiiiiccccccccccccaaaaaaaaaaaaaattttttttttttttteeeeeeeeeeeeedddddddddddddddddddd
		std::vector<std::string> sortedArguments = {"", to_string(NO_PRICE_FILTER), '0', '0', '0', "" };
		for (auto itr = commandDetails.arguments.begin(); itr != commandDetails.arguments.end(); itr++)
			for (int i = 0; i < SERACH_FIELDS.size(); i++)
				if (SERACH_FIELDS[i] == itr->first)
					sortedArguments[i] = itr->second;
		std::string searchResault = filmBox->search(sortedArguments[0], sortedArguments[1], sortedArguments[2], sortedArguments[3], sortedArguments[4], sortedArguments[5]);
		std::cout << "Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
		for (int j = 0; j < searchResault.size(); ++j)
			std::cout << j + 1 << ". " << films[j]->printInfo();
	}
}

void SystemInterface::checkAccessibilityLevel(void)
{
	if (currentUser == NO_USER && (commandDetails.command != "signup" || commandDetails.command != "login"))
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
	for (auto itr = registeredCustomers.begin(); itr != registeredCustomers.end(); ++itr)
		if (itr->second->getUsername() == newUsername)
			return;
	throw new BadRequest();
}

void SystemInterface::signup(void)
{
	this->handleSignupErrors();
	std::string customerType = getArgument("publisher", commandDetails.arguments);
	if (customerType == ARG_NOT_FOUND || customerType == "false") {
		int userId = idManager->makeNewUserId();
		currentUser = new Customer(getArgument("email", commandDetails.arguments), getArgument("username", commandDetails.arguments), 
																				   getArgument("password", commandDetails.arguments), 
																				   stoi(getArgument("age", commandDetails.arguments)), 
																				   userId);
		registeredCustomers.insert(std::pair<int, Customer*>(userId, currentUser));
	}
	else if (customerType == "true") {
		int userId = idManager->makeNewUserId();
		currentUser = new Publisher(getArgument("email", commandDetails.arguments), getArgument("username", commandDetails.arguments), 
																				    getArgument("password", commandDetails.arguments), 
																				    stoi(getArgument("age", commandDetails.arguments)), 
																				    userId);
		registeredCustomers.insert(std::pair<int, Customer*>(userId, currentUser));
	}
	else
		throw new BadRequest();
	std::cout << "OK" << std::endl;
}

void SystemInterface::login(void)
{
	std::string username, password;
	for (auto itrCD = commandDetails.arguments.begin(); itrCD != commandDetails.arguments.end(); itrCD++) {
		if (itrCD->first == "username")
			username = itrCD->second;
		if (itrCD->first == "password")
			password = itrCD->second;
	}
	if (username.empty() || password.empty())
		throw new BadRequest();
	for (int j = 0; j < registeredCustomers.size(); j++)
		if (registeredCustomers[j]->checkLoginInfo[username, password]) {
				currentUser = registeredCustomers[j];
				return;
			}
	std::cout << "OK" << std::endl;
}

void SystemInterface::handleSignupErrors()
{
	bool found = false;
	if (commandDetails.arguments.size() != 4 && commandDetails.arguments.size() != 5)
		throw new BadRequest();
	for (auto itr = commandDetails.arguments.begin(); itr != commandDetails.arguments.end(); itr++) {
		for (int i = 0; i < SIGNUP_ARGUMENTS.size(); ++i)
			if (itr->first == SIGNUP_ARGUMENTS[i]) {
				found = true;
				break;
			}
			if (i == 1)
				this->checkDuplicationOfUsername(itr->second);
		if (found == false)
			throw new BadRequest();
	}
}

void SystemInterface::addFilm(void)
{
	std::vector<string> sortedArguments;
	for (int i = 0; i < FILM_ARGUMENTS.size(); i++)
		sortedArguments.push_back(getArgument(FILM_ARGUMENTS[i], commandDetails.arguments));

	Film* newFilm = new Film(sortedArguments[0], sortedArguments[1], 
							 sortedArguments[2], sortedArguments[3], 
							 sortedArguments[4], sortedArguments[5], 
							 DEFAULT_ID);
	currentUser->addFilm(newFilm);
	newFilm->setId(idManager->makeNewFilmId());
	filmbox->addFilm(newFilm);
	std::cout << "OK" << std::endl;
}

void SystemInterface::followPub(int id)
{
	for (int i = 0; i < registeredCustomers.size(); ++i)
		if (registeredCustomers[i]->getId() == id) {
			currentUser->follow(registeredCustomers[i]);
			// registeredCustomers[i]->addFollower(currentUser);
			// currentUser->sendMessage(registeredCustomers[i], );
			return;
		}
	throw new NotFound();
}

// void SystemInterface::sellFilm(int filmId)
// {
// 	currentUser->buyFilm(this->findFilmById(filmId));
// 	//send message to pub ?????????????????????????????????????????????????????????????????
// }

Film* SystemInterface::findFilmById(int id)
{
	for (int i = 0; i < filmBox.size(); i++)
		if (filmBox[i].getId == filmId)
			return filmBox[i];
	throw new NotFound();
}

std::string readLine(int& foundCharPlace, std::string inputLine, int previousPlace)
{
	std::string separatedPiece;
	foundCharPlace = inputLine.find_first_of(' ', foundCharPlace + 1);
	separatedPiece = inputLine.substr(previousPlace + 1, foundCharPlace - previousPlace - 1);
	if (separatedPiece == "notifications")
		separatedPiece += readline(foundCharPlace, inputLine, foundCharPlace);
	return separatedPiece;
}

std::vector<std::string> separateInput(std::string inputLine)
{
	std::vector<std::string> separatedCommand;
	std::string separatedPiece;
	int foundCharPlace = 0, previousPlace = -1;
	
	while (foundCharPlace != -1)
	{
		// foundCharPlace = inputLine.find_first_of(' ', foundCharPlace + 1);
		// separatedPiece = inputLine.substr(previousPlace + 1, foundCharPlace - previousPlace - 1);

		separatedPiece = readLine(foundCharPlace, inputLine, previousPlace);

		if (separatedPiece != "?")
			separatedCommand.push_back(separatedPiece);

		previousPlace = foundCharPlace;
	}
	return separatedCommand;
}

void handleInputErrors(std::vector<std::string> separatedCommand)
{
	if ((!(separatedCommand.size() % 2) && separatedCommand.size() != 0) || separatedCommand.size() == 3)
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
		for (int k = 2; k < separatedCommand.size(); k *= 2) {
			// this->checkArguments(separatedCommand[k], separatedCommand[k + 1]);
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