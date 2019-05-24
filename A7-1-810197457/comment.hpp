#ifndef COMMENT_HPP
#define COMMENT_HPP

#include "customer.hpp"
// #include "publisher.hpp"
#include <string>
#include <vector>

class Comment
{
private:
	int id;
	std::string commentText;
	std::vector<Comment*> replies;
	Customer* sender;
public:
	Comment(std::string _content, int _id, Customer* _sender);
	Customer* getSender(void);
	int getId(void);
	void putReplay(Comment* replay);
	void print(void);
};

#endif