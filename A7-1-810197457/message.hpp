#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

class Message
{
public:
	Message(std::string _content);
	std::string getText(void);
	bool notRead(void);
	void read(void);
protected:
	std::string content;
	bool readFlag;
};

#endif