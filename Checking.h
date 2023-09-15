#pragma once
#include "Account.h"
#include <string>
using namespace std;

class Checking : public Account {
	private:
		double minBalance;
		double monthlyFee;
	public:
		Checking();
		Checking(int, double, double, double);

		void closeMonth();
		string accountString();
};

