#include "message.hpp"
#include <string>

Message::Message(std::string _content) 
{ 
	content = _content; 
	readFlag = false;
}

std::string Message::getText(void) { return content; }

bool Message::notRead(void) { return !readFlag; }

void Message::read(void) { readFlag = true; }