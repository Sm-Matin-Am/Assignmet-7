#include <string>
#include <sstream>
#include "handlers.hpp"

using namespace std;

loginPage::loginPage(SystemInterface* si) : systemInterface(si) {}

Response* loginPage::callback(Request*)
{
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");

	ostringstream body;
	
	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<div class='container'>" << endl
	if (stoi(req->getQueryParam("alertId")) == 1){
		body
		<< "<div class='alert alert-danger alert-dismissible fade show'>" << endl
    	<< "	<button type='button' class='close' data-dismiss='alert'>&times;</button>" << endl
    	<< "	<strong>Failed!</strong> username or password is wrong! Please try again." << endl
  		<< "</div>" << endl; break;
	}
	else if (stoi(req->getQueryParam("alertId")) == 2) {
		body
		<< "<div class='alert alert-danger alert-dismissible fade show'>" << endl
    	<< "	<button type='button' class='close' data-dismiss='alert'>&times;</button>" << endl
    	<< "	<strong>Danger!</strong> Last user's account is still in system available! Please first logout then try again!" << endl
  		<< "</div>" << endl; break;
	}
	<< "	<h2>Login form</h2>" << endl
	<< "	<form action='/checkLoginStatus' method='POST' class='was-validated'>" << endl
	<< "	<div class='form-group'>" << endl
	<< "		<label for='username'>Username:</label>" << endl
	<< "		<input type='text' id='username' class='form-control' placeholder='Enter username' name='username' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl
	<< "    </div>" << endl
	<< "    <div class='form-group'>" << endl
	<< "    	<label for='password'>Password:</label>" << endl
	<< "    	<input type='password' id='password' class='form-control' placeholder='Enter password' name='passsword' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl
	<< "    </div>" << endl
	<< "    <button type='submit' class='btn btn-primary'>Login</button>" << endl
	<< "	</form>" << endl
	<< "<br><br><a href='signupPage'>Don't have an account ?</a>" << endl
	<< "</div>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;
	
	res->setBody(body.str());
    return res;
}

signupPage::signupPage(SystemInterface* si) : systemInterface(si) {}

Response* signupPage::callback(Request*)
{
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");

	ostringstream body;
	
	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<div class='container'>" << endl;
	switch (stoi(req->getQueryParam("alertId"))) {
		case 1:
		body
		<< "<div class='alert alert-danger alert-dismissible fade show'>" << endl
    	<< "	<button type='button' class='close' data-dismiss='alert'>&times;</button>" << endl
    	<< "	<strong>Failed!</strong> password and it's confirm are not same !" << endl
  		<< "</div>" << endl; break;
  		case 2:
  		body
		<< "<div class='alert alert-warning alert-dismissible fade show'>" << endl
    	<< "	<button type='button' class='close' data-dismiss='alert'>&times;</button>" << endl
    	<< "	<strong>Warning!</strong> Your selected username has been used before by other users. Please try another one." << endl
  		<< "</div>" << endl; break;
  		case 3:
  		body
		<< "<div class='alert alert-danger alert-dismissible fade show'>" << endl
    	<< "	<button type='button' class='close' data-dismiss='alert'>&times;</button>" << endl
    	<< "	<strong>Danger!</strong> Last user's account is still in system available! Please first logout then try again!" << endl
  		<< "</div>" << endl; break;
  		default:;
  	}
  	body
	<< "	<h2>Signup form</h2>" << endl
	<< "	<form action='/checkSignupStatus' method='POST' class='was-validated'>" << endl
	<< "	<div class='form-group'>" << endl
	<< "		<label for='email'>Email:</label>" << endl
	<< "		<input type='email' id='email' class='form-control' placeholder='Enter email' name='email' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl
	<< "    </div>" << endl
	<< "    <div class='form-group'>" << endl
	<< "    	<label for='username'>Username:</label>" << endl
	<< "    	<input type='text' id='username' class='form-control' placeholder='Enter username' name='username' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl	
	<< "    </div>" << endl
	<< "    <div class='form-group'>" << endl
	<< "    	<label for='password'>Password:</label>" << endl
	<< "    	<input type='password' id='password' class='form-control' placeholder='Enter password' name='passsword' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl
	<< "    </div>" << endl
	<< "    <div class='form-group'>" << endl
	<< "    	<label for='confirm-pwd'>Confirm password:</label>" << endl
	<< "    	<input type='password' id='confirm-pwd' class='form-control' placeholder='Enter password agian' name='confirm' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl	
	<< "    </div>" << endl
	<< "    <div class='form-group'>" << endl
	<< "    	<label for='age'>Age:</label>" << endl
	<< "    	<input type='number' min='1' id='age' class='form-control' placeholder='Enter your age' name='age' required>" << endl
	<< "        <div class='valid-feedback'>Valid.</div>" << endl
    << "        <div class='invalid-feedback'>Please fill out this field.</div>" << endl	
	<< "    </div>" << endl
	<< "	<div class='form-group form-check'>" << endl
    << "		<label class='form-check-label'>" << endl
    << "		<input class='form-check-input' type='checkbox' name='accountType'> I am a publisher." << endl
    << "		</label>" << endl
    << "	</div>" << endl
	<< "    <button type='submit' class='btn btn-primary'>Signup</button>" << endl
	<< "<br><br><a href='signupPage'>Don't have an account ?</a>" << endl
	<< "	</form>" << endl
	<< "</div>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;
	
	res->setBody(body.str());
    return res;
}

checkLoginStatus::checkLoginStatus(SystemInterface* si) : systemInterface(si) {}

Response* checkLoginStatus::callback(Request* req)
{
	int newId;
	try {
		newId = systemInterface->login(req->getBodyParam("username"), req->getBodyParam("password"));
	} catch (exception* ex) {
		if(ex->what() == "BadRequest")//*******************************************
			return Response::redirect("/?alertId=1");
		else if(ex->what() == "PermissionDenied")
			return Response::redirect("/?alertId=2");
	}
	Response* res = Response::redirect("/SetListedFilms");
	res->setSessionId(to_string(newId));
	return res;
}

checkSignupInfo::checkSignupInfo(SystemInterface* si) : systemInterface(si) {}

Response* checkSignupInfo::callback(Request* req)
{
	int newId;
	if (req->getBodyParam("confirm") != req->getBodyParam("password")) {
		return Response::redirect("/signupPage?alertId=1");//********************************comment why has it happened
	}
	try {
		newId = systemInterface->signup(
						req->getBodyParam("email"),
						req->getBodyParam("username"),
						req->getBodyParam("password"),
						req->getBodyParam("age"),
						req->getBodyParam("accountType"));
	} catch(exception* ex) {
		if(ex->what() == "BadRequest")//*******************************************
			return Response::redirect("/signupPage?alertId=2");
		else if(ex->what() == "PermissionDenied")
			return Response::redirect("/signupPage?alertId=3");
	}
	Response* res = Response::redirect("/SetListedFilms");
	res->setSessionId(to_string(newId));
	return res;
}

HomePage::HomePage(SystemInterface* si) : systemInterface(si) {}

Response* HomePage::callback(Request* req)
{
	int id = stoi(req->getSessionId());
	if (!id) return Response::redirect("/");
	Customer* currentUser = systemInterface->findUserById(id);

	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");

	ostringstream body;
	
	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<h1>Hello " << currentUser->getUsername() << "</h1>" << endl
	<< "<a href='/logout'>Logout</a>" << endl
	<< "<a href='/profile'>Profile</a>" << endl;
	if (currentUser->isPublisher()){
		// cout << "true" << endl;
 		body << "<a href='/filmRegisterationPage'>+ Add new film</a>" << endl;
	}
	std::vector<std::vector<Film*> > lists;
	lists.push_back(systemInterface->getListedPublishedFilms());
	lists.push_back(systemInterface->getListedSalableFilms());

	for (int k = 0; k < lists.size(); k++) {
		// if (lists[k].empty())
		// 	continue;
		if (!currentUser->isPublisher() && k == 0)
	  		continue;
		body
		<< "<table style='width:100%'>" << endl
		<< "	<caption>Films</caption>" << endl
 		<< "	<tr>" << endl
   		<< "		<th>Number</th>" << endl
   		<< "		<th>Name</th>" << endl 
   		<< "		<th>Price</th>" << endl
   		<< "		<th>Production Year</th>" << endl
   		<< "		<th>Length</th>" << endl
   		<< "		<th>Score</th>" << endl
   		<< "		<th>Director" << endl
   		<< "		<form action='/SetListedFilms' method='GET'>" << endl
   		<< "				Search director name:" << endl
   		<< "				<input type='search' name='searchedDirector'>" << endl
   		<< "				<input type='submit' value='search'>" << endl
   		<< "		</form>" << endl
 	   	<< "		</th>" << endl;
 	   	if (currentUser->isPublisher() && k != 1)
 	   		body << "	<th>&nbsp;</th>" << endl;
  		body << "	</tr>" << endl;
  	
  		for (int i = 0; i < lists[k].size(); i++)
	  	{
  			body 
  			<< "<tr>" << endl
  		  	<< "	<td>" << to_string(i + 1) << "</td>" << endl
  		  	<< "	<td><a href='/filmDetailsPage?filmId=" << to_string(lists[k][i]->getId()) << "'>"<< lists[k][i]->getName() << "</a></td>" << endl
  		  	<< "	<td>" << to_string(lists[k][i]->getPrice()) << "</td>" << endl
  		  	<< "	<td>" << to_string(lists[k][i]->getYear()) << "</td>" << endl
  		  	<< "	<td>" << to_string(lists[k][i]->getLength()) << "</td>" << endl
  		  	<< "	<td>" << to_string(lists[k][i]->getScore()) << "</td>" << endl
 		  	<< "	<td>" << lists[k][i]->getDirector() << "</td>" << endl;
 		  	if (currentUser->isPublisher() && k != 1) {
 		  		body
 		  		<< "	<td>"
 		  		<< "  	<form action='/deleteFilm' method='POST'>" << endl
		    	<< "    	<input type='hidden' name='filmId' value='" << lists[k][i]->getId() << "'>" << endl
		    	<< "		<input type='submit' value='delete'>" << endl
		    	<< "	</form>" << endl
		    	<< "	</td>" << endl
  				<< "</tr>" << endl;
  			}
  		}
  		body << "</table><br><br><br>" << endl;
	}
	body << "</body>" << endl;
	body << "</html>" << endl;

	res->setBody(body.str());
    return res;
}

LogoutProcess::LogoutProcess(SystemInterface* si) : systemInterface(si) {}

Response* LogoutProcess::callback(Request* req)
{
	// try {
	systemInterface->logout();
	Response* res = Response::redirect("/");
	res->setSessionId("0");
	return res;
	// } catch (exception* ex) {
		// cout << ex->what() << endl;
		// return Response::redirect("??????")
	// }
}

SetListedFilms::SetListedFilms(SystemInterface* si) : systemInterface(si) {}

Response* SetListedFilms::callback(Request* req)
{
	Customer* currentUser = systemInterface->findUserById(stoi(req->getSessionId()));
	
	if (currentUser->isPublisher())
		systemInterface->setPublishedFilms(currentUser->getPublishedFilms(), req->getQueryParam("searchedDirector"));
	systemInterface->setSalableFilms(currentUser->getBalance(), req->getQueryParam("searchedDirector"));

	return Response::redirect("/HomePage");
}

DeleteFilm::DeleteFilm(SystemInterface* si) : systemInterface(si) {}

Response* DeleteFilm::callback(Request* req)
{
	int filmId = stoi(req->getBodyParam("filmId"));
	systemInterface->removeFilm(filmId);
	return Response::redirect("/SetListedFilms");	
}

RegisterFilm::RegisterFilm(SystemInterface* si) : systemInterface(si) {}

Response* RegisterFilm::callback(Request* req)
{
	try {
		systemInterface->addFilm(req->getBodyParam("name"), req->getBodyParam("year"), 
								 req->getBodyParam("length") , req->getBodyParam("price"), 
								 req->getBodyParam("summary"), req->getBodyParam("director"));
	} catch (exception* ex) {
		cout << ex->what() << endl;
		return Response::redirect("/filmRegisterationPage");
	}
	return Response::redirect("/SetListedFilms");
}

FilmRegisteration::FilmRegisteration(SystemInterface* si) : systemInterface(si) {}

Response* FilmRegisteration::callback(Request*)
{
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");

	ostringstream body;

	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<h1>Film Registeration Page</h1>" << endl
	<< "<a href='/logout'>Logout</a>" << endl
	<< "<a href='/profile'>Profile</a>" << endl
 	<< "<a href='/SetListedFilms'>Home</a>" << endl
	<< "<p>Hello my friend!</p>" << endl
	<< "<p>Please fill in the blanks:</p>" << endl
	<< "<form action='/addNewFilm' method='POST'>" << endl
	<< "	NAME:    <input type='text' name='name'><br>" << endl
	<< "	PRODUCTION YEAR: <input type='number' name='year' min='1900'><br>" << endl
	<< "	LENGTH: <input type='number' name='length' min='1'><br>" << endl
	<< "	PRICE:  <input type='number' name='price' min='0'><br>" << endl
	<< "	SUMMARY:      <input type='text' name='summary'><br>" << endl
	<< "	DIRECTOR:      <input type='text' name='director'><br><br>" << endl
	<< "	<input type='submit' value='register'>" << endl
	<< "	<input type='reset'" << endl
	<< "</form>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;

	res->setBody(body.str());
	return res;
}

BuyFilm::BuyFilm(SystemInterface* si) : systemInterface(si) {}

Response* BuyFilm::callback(Request* req)
{
	systemInterface->sellFilm(stoi(req->getBodyParam("filmId")));//Query
	return Response::redirect("/filmDetailsPage?filmId=" + req->getBodyParam("filmId"));//?????????????????????????????????????????????????????
}

RateFilm::RateFilm(SystemInterface* si) : systemInterface(si) {}

Response* RateFilm::callback(Request* req)
{
	systemInterface->rateFilm(stoi(req->getBodyParam("filmId")), stoi(req->getBodyParam("score")));//Query
	return Response::redirect("/filmDetailsPage?filmId=" + req->getBodyParam("filmId"));
}

Profile::Profile(SystemInterface* si) : systemInterface(si) {}

Response* Profile::callback(Request* req)
{
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	Customer* currentUser = systemInterface->findUserById(stoi(req->getSessionId()));
	
	ostringstream body;
	
	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<h1>Hello " << currentUser->getUsername() << "</h1>" << endl
	<< "<a href='/logout'>Logout</a>" << endl
	<< "<a href='/SetListedFilms'>Home</a>" << endl
	<< "<form action='/chargeAccount' method='POST'>" << endl
	<< "	<h3>Balance:</h3>"
	<< "	<input type='text' name='Budget' value='" << to_string(currentUser->getBalance()) << "'>"
	<< "	<input type='submit' value='deposit'>" << endl
	<< "</form>" << endl;

	vector<Film*> purchasedFilms = currentUser->getPurchasedFilms();
	body
	<< "<table style='width:100%'>" << endl
	<< "	<caption>Films</caption>" << endl
 	<< "	<tr>" << endl
   	<< "		<th>Number</th>" << endl
   	<< "		<th>Name</th>" << endl 
   	<< "		<th>Price</th>" << endl
   	<< "		<th>Production Year</th>" << endl
   	<< "		<th>Length</th>" << endl
   	<< "		<th>Score</th>" << endl
   	<< "		<th>Director</th>" << endl
  	<< "	</tr>" << endl;

	for (int j = 0; j < purchasedFilms.size(); j++) {
  		body 
  		<< "<tr>" << endl
  		<< "	<td>" << to_string(j + 1) << "</td>" << endl
  		<< "	<td><a href='/filmDetailsPage?filmId=" << to_string(purchasedFilms[j]->getId()) << "'>"<< purchasedFilms[j]->getName() << "</a></td>" << endl
  	  	<< "	<td>" << to_string(purchasedFilms[j]->getPrice()) << "</td>" << endl
  	  	<< "	<td>" << to_string(purchasedFilms[j]->getYear()) << "</td>" << endl
	  	<< "	<td>" << to_string(purchasedFilms[j]->getLength()) << "</td>" << endl
	  	<< "	<td>" << to_string(purchasedFilms[j]->getScore()) << "</td>" << endl
 	  	<< "	<td>" << purchasedFilms[j]->getDirector() << "</td>" << endl;
 	}
  	body << "</table><br><br><br>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;
  	res->setBody(body.str());
  	return res;
}

ChargeAccount::ChargeAccount(SystemInterface* si) : systemInterface(si) {}

Response* ChargeAccount::callback(Request* req)
{
	Customer* currentUser = systemInterface->findUserById(stoi(req->getSessionId()));
	currentUser->increaseMoney(stoi(req->getBodyParam("budget")));

	return Response::redirect("/profile");
}

FilmDetails::FilmDetails(SystemInterface* si) : systemInterface(si) {}

Response* FilmDetails::callback(Request* req)
{
	cout << "1" << endl;
	Response* res = new Response;
	int filmId = stoi(req->getQueryParam("filmId"));
	res->setHeader("Content-Type", "text/html");
	Film* film = systemInterface->findFilmById(filmId);
	Customer* currentUser = systemInterface->findUserById(stoi(req->getSessionId()));
	cout << "2" << endl;

	ostringstream body;
	
	body
	<< "<!DOCTYPE html>" << endl
	<< "<html>" << endl
	<< "<head>" << endl
	<< "<meta charset='utf-8'>" << endl
    << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl
    << "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl
	<< "<title>Page Title</title>" << endl
	<< "</head>" << endl
	<< "<body>" << endl
	<< "<h1>Film:  " << film->getName() << "</h1>" << endl
	<< "<a href='/logout'>Logout</a>" << endl
	<< "<a href='/SetListedFilms'>Home</a>" << endl
	<< "<a href='/profile'>Profile</a><br><br><br>" << endl
	<< "<p>NAME:" << film->getName() << "</p>" << endl
	<< "<p>SCORE:" << film->getScore() << "</p>" << endl
	<< "<p>DIRECTOR:" << film->getDirector() << "</p>" << endl
	<< "<p>YEAR:" << film->getYear() << "</p>" << endl
	<< "<p>LENGTH:" << film->getLength() << "</p>" << endl
	<< "<p>PRICE:" << film->getPrice() << "</p>" << endl
	<< "<p>SUMMARY:" << film->getSummary() << "</p><br><br>"<< endl;
	cout << "3" << endl;

	if (!currentUser->alreadyHasBoughtFilm(filmId) && currentUser->getBalance() >= film->getPrice()) {
		body
		<< "<form action='/buyFilm' method='POST'>" << endl
		<< "	<p>Do you want to buy this film?</p>" << endl
		<< "	<input type='hidden' name='filmId' value='" << film->getId() << "'>" << endl
		<< "	<input type='submit' value='BUY'>" << endl
		<< "</form>" << endl;
	}
	else if (currentUser->alreadyHasBoughtFilm(filmId)){
		body
		<< "<form action='/rateFilm' method='POST'>" << endl
  		<< "	<input type='hidden' name='filmId' value='" << film->getId() << "'>" << endl
  		<< "	<select name='score'>" << endl;
  		for (int k = 1; k <= 10; k++) {
  		body << "<option value='" << k << "'>" << k << "</option>" << endl;
  		}
  		body
  		<< "	</select><br><br>" << endl
		<< "	<input type='submit' value='rate'>" << endl
		<< "</form>" << endl;
	}
	// else if (currentUser->alreadyHasBoughtFilm(filmId) && currentUser->getBalance() < film->getPrice())
	cout << "4" << endl;
	
	vector<Film*> recommendedFilms = systemInterface->getRecommendedFilms(filmId);
	body
	<< "<table style='width:100%'>" << endl
	<< "	<caption>Recommended Films</caption>" << endl
 	<< "	<tr>" << endl
   	<< "		<th>Number</th>" << endl
   	<< "		<th>Name</th>" << endl 
   	<< "		<th>Length</th>" << endl
   	<< "		<th>Director</th>" << endl
  	<< "	</tr>" << endl;
	cout << "5" << endl;
  	
	for (int i = 0; i < recommendedFilms.size() && i < 4; i++) {
  		body 
  		<< "<tr>" << endl
  		<< "	<td>" << to_string(i + 1) << "</td>" << endl
  		<< "	<td><a href='/filmDetailsPage?filmId=" << recommendedFilms[i]->getId() << "'>"<< recommendedFilms[i]->getName() << "</a></td>" << endl
	  	<< "	<td>" << to_string(recommendedFilms[i]->getLength()) << "</td>" << endl
 	  	<< "	<td>" << recommendedFilms[i]->getDirector() << "</td>" << endl
  		<< "</tr>" << endl;
 	}
	cout << "6" << endl;

  	body << "</table><br><br><br>" << endl
	<< "</body>" << endl
	<< "</html>" << endl;
	cout << "7" << endl;
	res->setBody(body.str());
	return res;
}