#include <iostream>
#include <string>
#include "classes.hpp"
#include "handlers.hpp"
#include "systemInterface.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	Server myServer(argc > 1 ? atoi(argv[1]) : 5000);
	SystemInterface myInterface;
	// std::string inputCommand;

	// while (getline(std::cin, inputCommand))
			// si.processInput(inputCommand);
	try {
		// myServer.get("/", new showStartingPage(&myInterface));
		myServer.get("/", new loginPage(&myInterface));
		myServer.get("/signupPage", new signupPage(&myInterface));
		myServer.get("/SetListedFilms", new SetListedFilms(&myInterface));
		myServer.get("/HomePage", new HomePage(&myInterface));
		myServer.get("/logout", new LogoutProcess(&myInterface));
		myServer.get("/filmRegisterationPage", new FilmRegisteration(&myInterface));
		myServer.get("/profile", new Profile(&myInterface));
		myServer.get("/filmDetailsPage", new FilmDetails(&myInterface));
		myServer.post("/checkLoginStatus", new checkLoginStatus(&myInterface));
		myServer.post("/checkSignupInfo", new checkSignupInfo(&myInterface));
		myServer.post("/deleteFilm", new DeleteFilm(&myInterface));
		myServer.post("/addNewFilm", new RegisterFilm(&myInterface));
		myServer.post("/buyFilm", new BuyFilm(&myInterface));
		myServer.post("/rateFilm", new RateFilm(&myInterface));
		myServer.post("/chargeAccount", new ChargeAccount(&myInterface));
	} catch (Server::Exception ex) {
		cerr << ex.getMessage() << endl;
	}
	// myServer.get();
	// myServer.get();
	// myServer.get();
	// myServer.get();
	// myServer.get();
	// myServer.get();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();
	// myServer.post();

	myServer.run();
	return 0;
}