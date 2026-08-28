#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
using namespace std;

class DepositScreen : public Screen
{
private:
	static void _PrintClientCard(Client client) {
		cout << "=================================\n";
		cout << "full name        : " << client.FullName() << endl;
		cout << "phone            : " << client.Phone << endl;
		cout << "Account nuumber  : " << client.AccountNumber << endl;
		cout << "balance          : " << client.Balance << endl;
		cout << "=================================\n";
	}


public:
	static void ShowDepositScreen() {
		DrawHeader("deposit screen");

		string accountNumber = clsInputValidate::ReadString("enter the account number of the client to deposit to ");
		Client client = Client::FindClient(accountNumber);
		while (client.IsEmptyClient()) {
			accountNumber = clsInputValidate::ReadString("account number doesnt exists , try again ");
			client = Client::FindClient(accountNumber);
		}
		_PrintClientCard(client);

		double amount = clsInputValidate::ReadDoubleNumber("\nenter the amount you wish to deposit");
		char answer;
		cout << "are you sure you want to deposit " << to_string(amount) << " to the client ? [y] [n] \n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			client.Deposit(amount);
			cout << "\ndeposit successfull \n";
		}

		_PrintClientCard(client);
	}
};

