#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
using namespace std;

class FindClientScreen : Screen
{
private:
	static void _PrintClientCard(Client client) {
		cout << "=================================\n";
		cout << "first name       : " << client.FirstName << endl;
		cout << "Last name        : " << client.LastName << endl;
		cout << "full name        : " << client.FullName() << endl;
		cout << "phone            : " << client.Phone << endl;
		cout << "email            : " << client.Email << endl;
		cout << "Account nuumber  : " << client.AccountNumber << endl;
		cout << "pincode          : " << client.Pincode << endl;
		cout << "balance          : " << client.Balance << endl;
		cout << "=================================\n";
	}

public:
	static void ShowFindClientScreen() {
		DrawHeader("find client screen");

		
		string accountNumber = clsInputValidate::ReadString("enter the account number of the client you want to find ");
		Client client = Client::FindClient(accountNumber);

		while (client.IsEmptyClient()) {
			accountNumber = clsInputValidate::ReadString("there is no client with such account number , try again ");
			client = Client::FindClient(accountNumber);
		}

		_PrintClientCard(client);

	}
};

