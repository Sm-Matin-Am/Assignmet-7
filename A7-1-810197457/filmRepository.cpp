#include "filmRepository.hpp"
#include "film.hpp"
#include "constValues.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void FilmRepository::addFilm(Film* film) 
{ 
	films.push_back(film);
	for (int i = 0; i < matrix.size(); i++)
		matrix[i].push_back(matrix[i][0] == DELETED ? DELETED : 0);
	std::vector<int> newfilm(matrix.empty() ? 1 : matrix[0].size());
	matrix.push_back(newfilm);
	for (int i = 0; i < matrix.size(); ++i)
		if (matrix[0][i] == DELETED)
			matrix[matrix.size() - 1][i] = DELETED;
}

void FilmRepository::deleteFilm(int id)
{
	for (int i = 0; i < films.size(); i++)
		if (films[i]->getId() == id) {
			films.erase(films.begin() + i);
			break;
		}
	for (int j = 0; j < matrix.size(); j++) {
		matrix[j][id - 1] = DELETED;
		matrix[id - 1][j] = DELETED;
	}
}

void FilmRepository::updateElements(int filmId, Customer* buyer)
{
	for (int k = 0; k < matrix.size(); k++)
		if (buyer->alreadyHasBoughtFilm(k + 1) && matrix[k][filmId - 1] != DELETED && k != filmId - 1) {
			matrix[filmId - 1][k] += 1;
			matrix[k][filmId - 1] += 1;
		}
}

int FilmRepository::chooseOlder(int indexOfBestFilm, int j) { if (indexOfBestFilm > j) return j; }

std::vector<Film*> FilmRepository::findRelatedFilms(int filmId)
{
	std::vector<Film*> relatedFilms;
	std::vector<int> choosedIndexes;
	int indexOfBestFilm;
	for (int j = 0; j < matrix.size(); ++j) {
		indexOfBestFilm = 0;
		if (j == filmId - 1)
			continue;
		if (std::find(choosedIndexes.begin(), choosedIndexes.end(), j) == choosedIndexes.end())
			continue;
		if (matrix[filmId - 1][j] > matrix[filmId - 1][indexOfBestFilm])
			indexOfBestFilm = j;
		else if (matrix[filmId][j] == matrix[filmId][indexOfBestFilm])
			indexOfBestFilm = this->chooseOlder(indexOfBestFilm, j);
		relatedFilms.push_back(findFilmById(indexOfBestFilm + 1));
		choosedIndexes.push_back(j);
	}
	return relatedFilms;
}

Film* FilmRepository::findFilmById(int id)
{
	for (int i = 0; i < films.size(); i++)
		if (films[i]->getId() == id)
			return films[i];
}

void FilmRepository::showRelatedFilms(Customer* user, int filmId)
{
	std::vector<Film*> relatedFilms = this->findRelatedFilms(filmId);
	for (int k = 0; k < relatedFilms.size(); ++k)
		if (user->alreadyHasBoughtFilm(relatedFilms[k]->getId()))
			relatedFilms.erase(relatedFilms.begin() + k);
	std::cout << "Recommendation Film" << std::endl;
	std::cout << "#. Film Id | Film Name | Film Length | Film Director" << std::endl;
	for (int k = 0; k < 4 && k < relatedFilms.size(); k++)
		std::cout << k + 1 << ". " << relatedFilms[k]->getId()
				  << " | " << relatedFilms[k]->getName()
				  << " | " << relatedFilms[k]->getLength() 
				  << " | " << relatedFilms[k]->getDirector()
				  << std::endl;
}

std::vector<Film*> FilmRepository::getFilms(void) { return films; }