#include "../server/server.hpp"
#include "systemInterface.hpp"
#include <iostream>

// class showStartingPage : public RequestHandler
// {
// public:
// 	showStartingPage(SystemInterface* si);
// 	Response* callback(Request*);
// private:
// 	SystemInterface* systemInterface;
// };

class loginPage : public RequestHandler
{
public:
	loginPage(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class signupPage : public RequestHandler//************************************capital letters**********************
{
public:
	signupPage(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class checkLoginStatus : public RequestHandler
{
public:
	checkLoginStatus(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class checkSignupInfo : public RequestHandler
{
public:
	checkSignupInfo(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class HomePage : public RequestHandler
{
public:
	HomePage(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class LogoutProcess : public RequestHandler
{
public:
	LogoutProcess(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class SetListedFilms : public RequestHandler
{
public:
	SetListedFilms(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class DeleteFilm : public RequestHandler
{
public:
	DeleteFilm(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class RegisterFilm : public RequestHandler
{
public:
	RegisterFilm(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class FilmRegisteration : public RequestHandler
{
public:
	FilmRegisteration(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class BuyFilm : public RequestHandler
{
public:
	BuyFilm(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class RateFilm : public RequestHandler
{
public:
	RateFilm(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class Profile : public RequestHandler
{
public:
	Profile(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class ChargeAccount : public RequestHandler
{
public:
	ChargeAccount(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};

class FilmDetails : public RequestHandler
{
public:
	FilmDetails(SystemInterface*);
	Response* callback(Request*);
private:
	SystemInterface* systemInterface;
};