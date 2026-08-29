#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include"DepositScreen.h"
#include"WithdrawScreen.h"
#include"AllClientsBalanceScreen.h"
#include"TransferScreen.h"
using namespace std;


class TransferHistoryScreen : public Screen
{
private:


public:
	static void ShowTransferHistoryScreen() {

		DrawHeader("transfer history screen ");

		vector<Client::TransferRecordObject> objects = Client::LoadTransferRecordObjectsFromFile();

		cout << "				list of (" << objects.size() << ") records\n";
		cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(25) << "Date/time" << setw(2) << "|"
			<< setw(20) << "acc. of sender" << setw(2) << "|"
			<< setw(20) << "acc. of receiver" << setw(2) << "|"
			<< setw(10) << "amount" << setw(2) << "|"
			<< setw(20) << "sender balance" << setw(2) << "|"
			<< setw(20) << "reciever balance" << setw(2) << "|"
			<< setw(10) << "user" << setw(2) << "|";

		cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n";

		for (Client::TransferRecordObject object : objects) {

			
			cout << left << setw(25) << object.DateAndTime << setw(2) << "|"
				<< setw(20) << object.accountNumberFrom << setw(2) << "|"
				<< setw(20) << object.accountNumberTo << setw(2) << "|"
				<< setw(10) << object.amount << setw(2) << "|"
				<< setw(20) << object.balanceFrom << setw(2) << "|"
				<< setw(20) << object.balanceTo << setw(2) << "|"
				<< setw(10) << object.user << setw(2) << "|\n";

		}
		cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
};

