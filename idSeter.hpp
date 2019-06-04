#ifndef ID_SETER_HPP
#define ID_SETER_HPP

#include <map>

class IdSeter
{
private:
	int maxFilmId;
	int maxUserId;
	std::map<int, int> maxCommentIds;
public:
	IdSeter();
	int makeNewFilmId(void);
	int makeNewUserId(void);
	int makeNewCommentId(int filmId);
};

#endif