#pragma once
#include "Checking.h"
using namespace std;


Checking::Checking() : Account() {
	minBalance = 0.0;
	monthlyFee = 0.0;
}

Checking::Checking(int idNumber, double initBalance, double initMinBal, double initMonthlyFee) : Account(idNumber, initBalance) {
	minBalance = initMinBal;
	monthlyFee = initMonthlyFee;
}

void Checking::closeMonth() {
	if (getBalance() < minBalance) {
		withdraw(monthlyFee);
	}
}

string Checking::accountString() {
	string tempStr = "Checking Account #" + to_string(getId()) + " has a balance of $" + to_string(getBalance());

	return (tempStr);
}