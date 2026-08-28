#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
using namespace std;

class AllClientsBalanceScreen : Screen
{
private:

public:
	static void ShowAllClientsBalanceScreen() {
		//Client::ShowAllBalancesOfClients();
		vector<Client>clients = Client::GetAllClientsList();
		DrawHeader("All clients balances screen", "list of (" +to_string(clients.size())+ ") clients");

		cout << "-------------------------------------------------------\n";
		cout << left << setw(15) << "account number" << setw(2) << "|"
			<< setw(20) << "Name" << setw(2) << "|"
			<< setw(15) << "balance" << setw(2) << "|";
		cout << "\n-------------------------------------------------------\n";

		

		if (clients.size() == 0)
			cout << "there are no clients saved in the system\n";

		for (Client client : clients) {
			cout << left << setw(15) << client.AccountNumber << setw(2) << "|"
				<< setw(20) << client.FullName() << setw(2) << "|"
				<< setw(15) << client.Balance << setw(2) << "|\n";
			

		}
		cout << "-------------------------------------------------------\n";

		double total = Client::GetTotalBalancesOfAllClients();

		cout << "\t\ttotal balance : " << total << " (" << clsUtil::NumberToText(total) << ")" << endl;




	}
};

