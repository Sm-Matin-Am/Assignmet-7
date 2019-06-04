#include "comment.hpp"
#include "customer.hpp"
// #include "publisher.hpp"
#include <iostream>
#include <vector>
#include <string>

Comment::Comment(std::string _content, int _id, Customer* _sender)
	: sender(_sender)
{
	commentText = _content;
	id = _id;
}

Customer* Comment::getSender(void) { return sender; }

void Comment::putReplay(Comment* replay) { replies.push_back(replay); }

void Comment::print(void)
{
	std::cout << id << " " << commentText << std::endl;
	for (int i = 0; i < replies.size(); i++) {
		std::cout << i + 1 << ". ";
		replies[i]->print();
	}
}

int Comment::getId(void) { return id; }