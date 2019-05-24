// #include "exceptions.hpp"
#include <iostream>
#include <string>

class BadRequest : public std::exception 
{
public:
	const char* what() const noexcept { return "Bad Request"; }
};

class NotFound : public std::exception 
{
public:
	const char* what() const noexcept { return "Not Found"; }
};

class PermissionDenied : public std::exception 
{
public:
	const char* what() const noexcept { return "Permission Denied"; }
};