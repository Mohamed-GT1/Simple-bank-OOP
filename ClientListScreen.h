#pragma once
#include<iostream>
#include"Screen.h"
#include"Client.h"
using namespace std;

class ClientListScreen : public Screen
{
private:
	static void PrintClientLine(Client client) {
		cout << left << setw(20) << client.FullName() << setw(2) << "|"
			<< setw(15) << client.AccountNumber << setw(2) << "|"
			<< setw(8) << client.Pincode << setw(2) << "|"
			<< setw(20) << client.Phone << setw(2) << "|"
			<< setw(30) << client.Email << setw(2) << "|"
			<< setw(15) << client.Balance << setw(2) << "|";
	}
public:
	static void ShowAllCLientsScreen() {
		DrawHeader("All clients list screen");

		//Client::ShowAllClients();

		vector<Client> clients = Client::GetAllClientsList();

		cout << "				list of (" << clients.size() << ") clients\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(20) << "Name" << setw(2) << "|" << setw(15) << "account number" << setw(2) << "|" << setw(8) << "pincode" << setw(2) << "|"
			<< setw(20) << "phone number" << setw(2) << "|" << setw(30) << "Email" << setw(2) << "|"
			<< setw(15) << "balance" << setw(2) << "|";
		cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";

		if (clients.size() != 0) {

			for (Client client : clients) {

				PrintClientLine(client);
				cout << endl;


			}
		}
		else {
			cout << "     there are no clients saved       \n";
		}

		cout << "-----------------------------------------------------------------------------------------------------------------------\n";


	}
};

