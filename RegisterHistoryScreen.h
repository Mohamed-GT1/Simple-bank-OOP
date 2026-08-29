#pragma once
#include<iostream>
#include"User.h"
#include"Screen.h"
#include<vector>
#include<iomanip>
using namespace std;
class RegisterHistoryScreen : public Screen
{

private:

public:

	static void ShowRegisterHistoryScreen() {
		DrawHeader("register history screen");

		vector<User::LoginRecord> records = User::GetLoginRecordsHistory();


		cout << "				list of (" << records.size() << ") Records\n";
		cout << "----------------------------------------------------------------------------------\n";
		cout << left <<setw(25) <<"Date/time"<<setw(2)<<"|"
			<< setw(15) << "username" << setw(2) << "|"
			<< setw(15) << "Password" << setw(2) << "|"
			<< setw(20) << "Permission granted" << setw(2) << "|";
			
		cout << "\n----------------------------------------------------------------------------------\n";

		for (User::LoginRecord record : records) {

			cout << left << setw(25) << record.DateAndTime << setw(2) << "|"
				<< setw(15) << record.username << setw(2) << "|"
				<< setw(15) << record.password << setw(2) << "|"
				<< setw(20) << record.permissionGranted << setw(2) << "|\n";

		}
		cout << "----------------------------------------------------------------------------------\n";


	}
};

