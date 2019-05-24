#ifndef FILM_REPOSITORY_HPP
#define FILM_REPOSITORY_HPP

#include "film.hpp"
#include "customer.hpp"
#include <vector>

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

#endif