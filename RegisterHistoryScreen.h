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

		vector<string> lines = User::GetRegisterHistoryLinesOfString();


		cout << "				list of (" << lines.size() << ") clients\n";
		cout << "----------------------------------------------------------------------------------\n";
		cout << left <<setw(25) <<"Date/time"<<setw(2)<<"|"
			<< setw(15) << "username" << setw(2) << "|"
			<< setw(15) << "Password" << setw(2) << "|"
			<< setw(20) << "Permission granted" << setw(2) << "|";
			
		cout << "\n----------------------------------------------------------------------------------\n";

		for (string line : lines) {

			vector<string> dataOfLine= clsString::SplitString(line,"#//#");

			cout<<left<<setw(25)<<dataOfLine[0]<<setw(2)<<"|"
				<< setw(15) << dataOfLine[1] << setw(2) << "|"
				<< setw(15) << dataOfLine[2] << setw(2) << "|"
				<< setw(20) << dataOfLine[3] << setw(2) << "|\n";

		}
		cout << "----------------------------------------------------------------------------------\n";


	}
};

