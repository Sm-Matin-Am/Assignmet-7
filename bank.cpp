#include "bank.hpp"
#include "exceptions.hpp"
#include <map>

void Bank::addAccount(int id)
{
	assets.insert(std::pair<int, double> (id, 0));
}

void Bank::deposite(int id, int money)
{
	searchAccount(id)->second += money;
}
	
int Bank::withdraw(int id)
{
	int withdrawalMoney = searchAccount(id)->second;
	searchAccount(id)->second = 0;
	return withdrawalMoney;
}
	
std::map<int, int>::iterator Bank::searchAccount(int id)
{
	for (auto itr = assets.begin(); itr != assets.end(); itr++)
		if (itr->first == id)
			return itr;
	throw new NotFound();
}