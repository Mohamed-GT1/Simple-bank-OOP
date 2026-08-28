#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
using namespace std;

class UpdateClientScreen : public Screen 
{
private:
	static void _UpdateClientFromUser(Client& client) {
		client.FirstName = clsInputValidate::ReadString("enter the first name :");
		client.LastName = clsInputValidate::ReadString("enter the last name :");
		client.Phone = clsInputValidate::ReadString("enter Phone number :");
		client.Email = clsInputValidate::ReadString("enter email :");
		client.Pincode = clsInputValidate::ReadString("enter pincode :");
		client.Balance = clsInputValidate::ReadDoubleNumber("enter Balance :");


	}
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

	static void ShowUpdateClientScreen() {
		DrawHeader("update client screen");
		//Client::UpdateClient();

		string accountNumber = clsInputValidate::ReadString("enter the account number you wish to update ");
		Client client = Client::FindClient(accountNumber);
		while (client.IsEmptyClient())
		{
			cout << "account number does not exist , choose another one \n";
			getline(cin, accountNumber);
			client = Client::FindClient(accountNumber);
		}

		_PrintClientCard(client);
		cout << endl;

		_UpdateClientFromUser(client);

		Client::SaveResult sr = client.Save();

		switch (sr) {
		case(Client::SaveResult::FailedEmpty):
			cout << "error saving , the client is empty \n";
			break;

		case(Client::SaveResult::SuccessFull):
			cout << "\nsuccessfully updated the client \n\n";
			//client.Print();
			_PrintClientCard(client);
			break;

		case(Client::SaveResult::FailedAccountExists):
			cout << "error saving , the client do already exists \n";
			break;
		}
	}
	

};

