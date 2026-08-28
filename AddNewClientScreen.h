#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
using namespace std;

class AddNewClientScreen : public Screen
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
	static void ShowAddNewClientScreen() {
		DrawHeader("Add new Client screen");
		//gotta separate the ui from the object , we later gonna remove this from client class bec it has ui functions 
		//Client::AddNewClient();

		string accountNumber = clsInputValidate::ReadString("enter the account number of the client to add ");

		while (Client::DoesClientExist(accountNumber)) {
			cout << "this account number already exists for a client , try another one \n";
			accountNumber = clsInputValidate::ReadString("enter the account number of the client to add ");
		}

		Client client = Client::_GetAddNewClientObject(accountNumber);

		_UpdateClientFromUser(client);

		Client::SaveResult sr = client.Save();

		//Client::PrintSaveResult(sr, client);

		switch (sr) {
		case(Client::SaveResult::FailedEmpty):
			cout << "error saving , the client is empty \n";
			break;

		case(Client::SaveResult::SuccessFull):
			cout << "successfully added the client \n";
			//client.Print();
			_PrintClientCard(client);
			break;

		case(Client::SaveResult::FailedAccountExists):
			cout << "error saving , the client do already exists \n";
			break;
		}
	}
};


//maybe todo later :
//dont like the repeation of the switch for the save reesult in each class,maybe put PrintSaveResult in the screen superclass

