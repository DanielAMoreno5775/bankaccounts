//definitions for member functions of the Account class

#pragma once
#include "Account.h"
#include <iostream>
using namespace std;

//constructors with different default values to identify problem
Account::Account() {
	id = 0;
	balance = 0.0;
}
Account::Account(int identificationNum = -1, double bal = -1.0) {
	id = identificationNum;
	balance = bal;
}

//mutators
void Account::setId(int identificationNum) {
	id = identificationNum;
}
void Account::setBalance(double bal) {
	balance = bal;
}
void Account::withdraw(double quantityToWithdraw) {
	if (balance < quantityToWithdraw) {
		cout << "Failed Withdrawal - Withdrew More Money Than Is Present - " << quantityToWithdraw << endl;
	} else {
		balance -= quantityToWithdraw;
	}
}
void Account::deposit(double quantityToDeposit) {
	balance += quantityToDeposit;
}

//getters
int Account::getId() const {
	return id;
}
double Account::getBalance() const {
	return balance;
}