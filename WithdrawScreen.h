#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
using namespace std;


class WithdrawScreen : public Screen
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
	static void ShowWithdrawScreen() {
		DrawHeader("withdraw screen");

		string accountNumber = clsInputValidate::ReadString("enter the account number to withdraw from ");
		Client client = Client::FindClient(accountNumber);

		while (client.IsEmptyClient()) {
			accountNumber = clsInputValidate::ReadString("client with account number doesnt exist, try again ");
			 client = Client::FindClient(accountNumber);
		}

		_PrintClientCard(client);

		double amount = clsInputValidate::ReadDoubleNumber("\nenter the amount you wish to withdraw ");
		char answer = clsInputValidate::ReadChar("are you sure you want to withdraw " + to_string(amount) + " ? [y] [n]");
		
		if (answer == 'y' || answer == 'Y') {

			while(!client.Withdraw(amount)) {
				cout << "cannot withdraw amount, amount exceeds balance\n";
				cout << "the maximum amount to withdraw is " + to_string(client.Balance)<<endl;
				amount= clsInputValidate::ReadDoubleNumber("\nenter the amount you wish to withdraw ");
			}
			
			cout << "\nsuccessfull withdarw\n";
			_PrintClientCard(client);
			
		}
		else {
			cout << "\nwithdraw Cancelled \n";
		}
		
	}
};

