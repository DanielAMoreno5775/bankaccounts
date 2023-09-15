#pragma once
#include "Account.h"
#include <string>
using namespace std;

class Savings : public Account {
private:
	double minBalance;
	double annualInterestRate;
public:
	Savings();
	Savings(int, double, double, double);

	void closeMonth();
	string accountString();
};

