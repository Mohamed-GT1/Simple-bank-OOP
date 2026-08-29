#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
using namespace std;

class TransferScreen : public Screen
{
private : 
	

	static void printClientCard(Client client) {
		cout << "=================================\n";
		cout << "full name        : " << client.FullName() << endl;
		cout << "email            : " << client.Email << endl;
		cout << "Account nuumber  : " << client.AccountNumber << endl;
		cout << "balance          : " << client.Balance << endl;
		cout << "=================================\n\n";
	}

	

public:
	static void ShowTransferScreen() {
		DrawHeader("transfer screen");

		string accountNumberClient1 = Client::ReadAccountNumber("enter the account number of the client to transfer from");
		Client client1 = Client::FindClient(accountNumberClient1);
		printClientCard(client1);


		string accountNumberClient2 = Client::ReadAccountNumber("enter the account number of the client to transfer to");
		Client client2 = Client::FindClient(accountNumberClient2);
		printClientCard(client2);

		double amount = clsInputValidate::ReadDoubleNumber("enter the amount you wish to transfer");
		while (amount > client1.Balance) {
			amount= clsInputValidate::ReadDoubleNumber("the amount exceeds the client balance , try again");
		}

		char answer = clsInputValidate::ReadChar("are you sure you want to perform this transfer operation? [y] [n] ");
		if (answer == 'n' || answer == 'N') {
			cout << "\ntransfer cancelled\n";
			return;
		}


		if (Client::TransferFromClient1ToClient2(client1, client2, amount,CurrentUser.Username)) {
			cout << "\nsuccessfull transfer \n\n";
			printClientCard(client1);
			printClientCard(client2);
		}
		else {
			cout << "\nFailed transfer\n";
		}
		
	}
};

