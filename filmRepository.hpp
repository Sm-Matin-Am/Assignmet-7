#ifndef FILM_REPOSITORY_HPP
#define FILM_REPOSITORY_HPP

#include "film.hpp"
#include "customer.hpp"
#include <vector>

class FilmRepository
{
private:
	std::vector<Film*> films;
	// std::vector<Film*> topFilms;
	std::vector<std::vector<int> > matrix;
public:
	void addFilm(Film* film);
	void deleteFilm(int id);
	void updateElements(int filmId, Customer* buyer);
	void showRelatedFilms(Customer* user, int filmId);
	int chooseOlder(int indexOfBestFilm, int j, int filmId);
	Film* findFilmById(int id);
	std::vector<Film*> findRelatedFilms(int filmId);
	std::vector<Film*> getFilms(void);
};

#endif