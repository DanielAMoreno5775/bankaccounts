//header file for an abstract base class called Account

#pragma once
#include <string>
using namespace std;

class Account {
	private:
		int id;
		double balance;
	public:
		Account();                          //constructor prototype
		Account(int, double);               //overloaded constructor prototype

		void setId(int);
		void setBalance(double);
		void withdraw(double);
		void deposit(double);
		int getId() const;
		double getBalance() const;

		//pure virtual functions
		virtual string accountString() = 0;
		virtual void closeMonth() = 0;
};

