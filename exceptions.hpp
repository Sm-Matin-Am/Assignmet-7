#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

// #include <iostream>

// class BadRequest : public std::exception ;
// class NotFound : public std::exception ;
// class PermissionDenied : public std::exception ;

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

#endif