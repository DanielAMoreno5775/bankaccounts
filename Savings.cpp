#pragma once
#include "Savings.h"
using namespace std;

Savings::Savings() : Account() {
	minBalance = 0.0;
	annualInterestRate = 0.0;
}

Savings::Savings(int idNumber, double initBalance, double initMinBal, double initAnnualInterestRate) : Account(idNumber, initBalance) {
	minBalance = initMinBal;
	annualInterestRate = initAnnualInterestRate;
}

void Savings::closeMonth() {
	double monthlyInterestRate = (annualInterestRate / 12.0) / 100.0; //also converts % to decimal
	double interestDeposit = 0.0;

	if (getBalance() > minBalance) {
		interestDeposit = (getBalance() * monthlyInterestRate);
		deposit(interestDeposit);
	}
}

string Savings::accountString() {
	string tempStr = "Savings Account #" + to_string(getId()) + " has a balance of $" + to_string(getBalance());

	return (tempStr);
}