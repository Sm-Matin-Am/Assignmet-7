#include "idSeter.hpp"
#include <map>

IdSeter::IdSeter(void)
{
	maxFilmId = 0;
	maxUserId = 0;
}

int IdSeter::makeNewCommentId(int filmId) 
{ 
	for (auto itr = maxCommentIds.begin(); itr != maxCommentIds.end(); ++itr)
		if (itr->first == filmId)
			return ++itr->second;
	maxCommentIds.insert(std::pair<int, int>(filmId, 1));
	return 1;
}

int IdSeter::makeNewUserId(void) { return ++maxUserId; }

int IdSeter::makeNewFilmId(void) { return ++maxFilmId; }
