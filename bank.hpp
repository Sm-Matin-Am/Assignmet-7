#ifndef BANK_HPP
#define BANK_HPP

#include <map>

class Bank
{
private:
	std::map<int, int> assets;
public:
	void addAccount(int id);
	void deposite(int id, int money);
	int withdraw(int id);
	std::map<int, int>::iterator searchAccount(int id);
};

#endif