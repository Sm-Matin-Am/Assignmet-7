#include "filmRepository.hpp"
#include "film.hpp"
#include <iostream>
#include <string>
#include <vector>

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
	if (indexOfBestFilm > k)
		indexOfBestFilm = k;
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
	std::cout << "Recommendation Film" << std::endl;
	std::cout << "#. Film Id | Film Name | Film Lenght | Film Director" << std::endl;
	for (int j = 0; j < 4 && j < topFilms.size(); j++)
		std::cout << j + 1 << ". " << topFilms[j]->getId()
				  << " | " << topFilms[j]->getName()
				  << " | " << topFilms[j]->getLength() 
				  << " | " << topFilms[j]->getDirector()
				  << std::endl;
}

std::vector<Film*> FilmRepository::getFilms(void) { return films; }