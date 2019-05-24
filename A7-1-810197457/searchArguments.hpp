#ifndef SEARCH_ARGUMENTS_HPP
#define SEARCH_ARGUMENTS_HPP

#include "constValues.hpp"
#include <vector>
#include <string>

const std::vector<std::string> CORRECT_COMMAND_TITLES = { POST, PUT, DELETE, GET }; 
const std::vector<std::string> CORRECT_COMMAND_BODIES = { "signup", "login", "films", "money", 
														"replies", "followers", "buy", "rate", 
														"comments", "published", "purchased", 
														"notifications",  "notifications read" };
const std::vector<std::string> SIGNUP_ARGUMENTS = { "email", "username", "password", "age", "publisher" };
const std::vector<std::string> FILM_ARGUMENTS = { "name", "year", "length" , "price", "summary", "director" };
const std::vector<std::string> SEARCH_FIELDS = { "name", "price", "min_year", "max_year", "min_rate", "director" };
const std::vector<std::string> LOGIN_ARGUMENTS = { "username", "password" };
const std::vector<std::string> REPLAY_ARGUMENTS = { "film_id", "comment_id", "content" };
const std::vector<std::string> RATE_ARGUMENTS = { "film_id", "score" };
const std::vector<std::string> COMMENT_ARGUMENTS = { "film_id", "content" };
const std::vector<std::string> BLANK_FIELDS = { "", std::to_string(NO_PRICE_FILTER), "0", "10000", "0", "" };
const std::vector<std::string> DELETE_COMMENT = { "film_id", "comment_id" };


#endif