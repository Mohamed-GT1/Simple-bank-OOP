#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
using namespace std;

class DeleteClientScreen : public Screen
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
	static void ShowDeleteClientScreen() {
		DrawHeader("delete client screen");
		//Client::DeleteClient();

		string accountNumber = clsInputValidate::ReadString("enter the account number of the client you want to delete ");
		Client client = Client::FindClient(accountNumber);

		while (client.IsEmptyClient()) {
			accountNumber = clsInputValidate::ReadString("account number doesnt exists , try again \nenter the account number of the client you want to delete ");
			client = Client::FindClient(accountNumber);
		}

		_PrintClientCard(client);

		char answer;
		cout << "are you sure you want to delete this client ? [y] [n] ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			if (client.Delete()) {
				cout << "\ndeleted successfully \n\n";
				_PrintClientCard(client);
			}
			else {
				cout << "error deleting client \n";
			}
		}
		else {
			cout << "client was not deleted \n";
		}

	}
};

