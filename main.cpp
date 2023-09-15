/*
Lab #07 C++

This program will read commands from a file and manipulate the savings/checking accounts as directed

by Daniel Moreno in COSC-1437-30001
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "Checking.h"
#include "Savings.h"
using namespace std;

void openInputFile(fstream&);
void readFileCommands(fstream&, Account* []);
void createSavingsAccountCommand(vector <string>&, int&, Account* []);
void createCheckingAccountCommand(vector <string>&, int&, Account* []);
void depositCommand(vector <string>&, int, Account* const []);
void withdrawCommand(vector <string>&, int, Account* const []);
void balanceCommand(vector <string>&, int, const Account* const []);
void closeCommand(int, Account* const []);
void reportCommand(int, Account* const []);
bool verifyCommand(string, string);
void split(const string&, char, vector <string>&);

int main() {
	const int MAX_NUM_OF_ACCOUNTS = 9;
	fstream dataFile;
	Account* arrayOfAccountPointers[MAX_NUM_OF_ACCOUNTS]{ nullptr };
	int numOfAccounts = -1;

	openInputFile(dataFile);

	readFileCommands(dataFile, arrayOfAccountPointers);

	dataFile.close();

	return 0;
}

void openInputFile(fstream& inFile) {
	string filename = "";
	cout << "Please enter the filename and/or the filepath: ";
	cin >> filename;
	inFile.open(filename, ios::in);

	//run if and until the user enters a valid filename/filepath
	while (inFile.fail()) {
		cout << endl << "======================" << endl << "That filename/filepath was invalid." << endl;
		cout << "Please enter the filename and/or the filepath: ";
		cin >> filename;
		inFile.open(filename, ios::in);
	}

	cout << "File Opened" << endl;
}

void readFileCommands(fstream& file, Account* accountArray[]) {
	int accountNum = -1,
		numEntries = 0;
	double balance = 0.0,
		quantity = 0.0;
	bool accountAlreadyExists = false,
		multipleWordsFlag = false;
	string line = "Placeholder";
	vector<string> componentsOfString;
	char delimiter = ' ';

	//reset position in file to beginning
	file.clear();
	file.seekg(0);

	// Continue reading until the end of file
	getline(file, line, '\n');
	while (file) {
		//reset everything for the next loop
		multipleWordsFlag = false;
		componentsOfString.clear();

		//ensure that I'm not trying to read a blank line
		if ((line != "\n") && (line != "") && (line != " ") && (line != "\t") && (line != "\v")) {
			for (int i = 1; i < line.length(); i += 1) {
				if (line[i] == ' ' && !multipleWordsFlag) {
					multipleWordsFlag = true;
				}
			}

			//if there is a space in the line, check for commands with multiple terms
			if (multipleWordsFlag) {
				split(line, delimiter, componentsOfString);
				//check whether first word of line is recognized command
				if (verifyCommand(componentsOfString[0], "Savings")) {
					createSavingsAccountCommand(componentsOfString, numEntries, accountArray);
				}
				else if (verifyCommand(componentsOfString[0], "Checking")) {
					createCheckingAccountCommand(componentsOfString, numEntries, accountArray);
				}
				else if (verifyCommand(componentsOfString[0], "Deposit")) {
					depositCommand(componentsOfString, numEntries, accountArray);
				}
				else if (verifyCommand(componentsOfString[0], "Withdraw")) {
					withdrawCommand(componentsOfString, numEntries, accountArray);
				}
				else if (verifyCommand(componentsOfString[0], "Balance")) {
					balanceCommand(componentsOfString, numEntries, accountArray);
				}
				else {
					cout << "Unrecognized Command - " << componentsOfString[0] << endl;
				}
			} else { //otherwise, check for commands with one term
				if (verifyCommand(line, "Close")) {
					closeCommand(numEntries, accountArray);
				}
				else if (verifyCommand(line, "Report")) {
					reportCommand(numEntries, accountArray);
				}
				else {
					cout << "Unrecognized Command - " << line << endl;
				}
			}
		}

		getline(file, line, '\n');
	}
}

void createSavingsAccountCommand(vector <string>& componentsOfString, int& numEntries, Account* accountArray[]) {
	int accountNum = -1,
		index = 0;
	double balance = 0.0,
		minBalance = 0.0,
		annualInterestRate = 0.0;
	bool accountAlreadyExists = false;
	string line = "Placeholder";
	Savings* anEntry = nullptr;

	accountNum = stoi(componentsOfString[1]);
	balance = stod(componentsOfString[2]);
	minBalance = stod(componentsOfString[3]);
	annualInterestRate = stod(componentsOfString[4]);


	//won't waste time trying to search an empty array
	if (numEntries == 0) {
		anEntry = new Savings(accountNum, balance, minBalance, annualInterestRate);

		accountArray[numEntries] = anEntry;
		cout << fixed << setprecision(2);
		cout << "Savings account number " << accountNum << " created" << endl;
		cout << "with an initial balance of $" << balance << endl;
		numEntries += 1;
	}
	else if (numEntries > 0) { //prevent while loop from throwing an error
		//iterate through already existing entries to ensure that account number hasn't already been used and stop looking if it finds accountNum
		while (index < numEntries && !accountAlreadyExists) {
			if (accountArray[index]->getId() == accountNum) {
				cout << "Invalid Command - Preexisting Account Number - " << accountNum << endl;
				accountAlreadyExists = true;
			}
			index++;
		}
		//if account number hasn't already been used, create new account
		if (accountAlreadyExists == false) {
			anEntry = new Savings(accountNum, balance, minBalance, annualInterestRate);

			accountArray[numEntries] = anEntry;
			cout << fixed << setprecision(2);
			cout << "Savings account number " << accountNum << " created" << endl;
			cout << "with an initial balance of $" << balance << endl;
			numEntries += 1;
		}
	}
}

void createCheckingAccountCommand(vector <string>& componentsOfString, int& numEntries, Account* accountArray[]) {
	int accountNum = -1,
		index = 0;
	double balance = 0.0,
		minBalance = 0.0,
		monthlyFee = 0.0;
	bool accountAlreadyExists = false;
	string line = "Placeholder";
	Checking* anEntry = nullptr;

	accountNum = stoi(componentsOfString[1]);
	balance = stod(componentsOfString[2]);
	minBalance = stod(componentsOfString[3]);
	monthlyFee = stod(componentsOfString[4]);


	//won't waste time trying to search an empty array
	if (numEntries == 0) {
		anEntry = new Checking(accountNum, balance, minBalance, monthlyFee);

		accountArray[numEntries] = anEntry;
		cout << fixed << setprecision(2);
		cout << "Checking account number " << accountNum << " created" << endl;
		cout << "with an initial balance of $" << balance << endl;
		numEntries += 1;
	}
	else if (numEntries > 0) { //prevent while loop from throwing an error
		//iterate through already existing entries to ensure that account number hasn't already been used and stop looking if it finds accountNum
		while (index < numEntries && !accountAlreadyExists) {
			if (accountArray[index]->getId() == accountNum) {
				cout << "Invalid Command - Preexisting Account Number - " << accountNum << endl;
				accountAlreadyExists = true;
			}
			index++;
		}
		//if account number hasn't already been used, create new account
		if (accountAlreadyExists == false) {
			anEntry = new Checking(accountNum, balance, minBalance, monthlyFee);

			accountArray[numEntries] = anEntry;
			cout << fixed << setprecision(2);
			cout << "Checking account number " << accountNum << " created" << endl;
			cout << "with an initial balance of $" << balance << endl;
			numEntries += 1;
		}
	}
}

void depositCommand(vector <string>& componentsOfString, int numEntries, Account* const accountArray[]) {
	int accountNum = -1;
	double quantity = 0.0;

	accountNum = stoi(componentsOfString[1]);
	quantity = stod(componentsOfString[2]);

	//ensure that account requested exists
	if (accountNum <= numEntries) {
		accountArray[accountNum - 1]->deposit(quantity);
		cout << fixed << setprecision(2);
		cout << "Deposited $" << quantity << " into account #" << accountNum << endl;
		cout << "current balance is $" << accountArray[accountNum - 1]->getBalance() << endl;
	}
	else {
		cout << "Failed Deposit - Invalid Account Number - " << accountNum << endl;
	}
}

void withdrawCommand(vector <string>& componentsOfString, int numEntries, Account* const accountArray[]) {
	int accountNum = -1;
	double quantity = 0.0;

	accountNum = stoi(componentsOfString[1]);
	quantity = stod(componentsOfString[2]);

	//ensure that account requested exists and has the necessary funds to withdraw
	if (accountNum <= numEntries && quantity <= accountArray[accountNum - 1]->getBalance()) {
		accountArray[accountNum - 1]->withdraw(quantity);
		cout << fixed << setprecision(2);
		cout << "Withdrew $" << quantity << " from account #" << accountNum << endl;
		cout << "current balance is $" << accountArray[accountNum - 1]->getBalance() << endl;
	}
	else if (accountNum > numEntries) {
		cout << "Failed Withdrawal - Invalid Account Number - " << accountNum << endl;
	}
	else if (quantity > accountArray[accountNum - 1]->getBalance()) {
		cout << fixed << setprecision(2);
		cout << "Failed Withdrawal - Request Exceeds Balance on Account #" << accountNum <<  " - $" << quantity << endl;
	}
}

void balanceCommand(vector <string>& componentsOfString, int numEntries, const Account* const accountArray[]) {
	int accountNum = -1;

	accountNum = stoi(componentsOfString[1]);

	if (accountNum <= numEntries) {
		cout << fixed << setprecision(2);
		cout << "Current balance in account #" << accountNum << " is $" << accountArray[accountNum - 1]->getBalance() << endl;
	}
	else {
		cout << "Failed Balance Display - Invalid Account Number - " << accountNum << endl;
	}
}

void closeCommand(int numEntries, Account* const accountArray[]) {
	for (int index = 0; index < numEntries; index += 1) {
		accountArray[index]->closeMonth();
	}
		
	cout << "End of month processing complete" << endl;
}

void reportCommand(int numEntries, Account* const accountArray[]) {
	for (int index = 0; index < numEntries; index += 1) {
		cout << fixed << setprecision(6);
		cout << accountArray[index]->accountString() << endl;
	}
}

bool verifyCommand(string wordPassed, string expectedCommand) {
	bool validCommandFlag = false;

	//eliminate problems from different cases
	for (int index = 0; index < wordPassed.length(); index += 1) {
		wordPassed[index] = toupper(wordPassed[index]);
	}
	for (int index = 0; index < expectedCommand.length(); index += 1) {
		expectedCommand[index] = toupper(expectedCommand[index]);
	}

	//check if string matches expected values
	if (wordPassed == expectedCommand) {
		validCommandFlag = true;
	}

	return validCommandFlag;
}

void split(const string& s, char delim, vector <string>& tokens) {
	int tokenStart = 0;
	int delimPosition;
	string tok;

	delimPosition = static_cast<int>(s.find(delim, 0));

	while (delimPosition != string::npos) {
		//extract token
		tok = s.substr(tokenStart, (delimPosition - tokenStart));
		//put token into vector
		tokens.push_back(tok);
		//move delimPosition ahead
		delimPosition += 1;
		//move tokenStart to delimPosition
		tokenStart = delimPosition;
		//find next occurrence of delimiter in s
		delimPosition = static_cast<int>(s.find(delim, delimPosition));
		//if not more delimiters, extract last token
		if (delimPosition == string::npos) {
			tok = s.substr(tokenStart, (delimPosition - tokenStart));
			tokens.push_back(tok);
		}
	}
}