#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
using namespace std;

class AllUsersScreen : public Screen
{
public:
	static void PrintUser(User  user) {

		cout << left << setw(15) << user.Username << setw(2) << "|"
			<< setw(10) << user.Password << setw(2) << "|"
			<< setw(20) << user.PermissionGranted << setw(2) << "|"
			<< setw(20) << user.FullName() << setw(2) << "|"
			<< setw(20) << user.Phone << setw(2) << "|"
			<< setw(20) << user.Email << setw(2) << "|";

		}

	static void ShowAllUsersScreen() {
		DrawHeader("All users screen");

		

			vector<User> users = User::GetListOfAllUsers();

			cout << "				list of (" << users.size() << ") clients\n";
			cout << "--------------------------------------------------------------------------------------------------------------------\n";
			cout << left << setw(15) << "username" << setw(2) << "|" 
				<< setw(10) << "Password" << setw(2) << "|"
				<< setw(20) << "Permission granted" << setw(2) << "|"
				<< setw(20) << "Full name" << setw(2) << "|"
				<< setw(20) << "phone" << setw(2) << "|"
				<< setw(20) << "email" << setw(2) << "|";
			cout << "\n--------------------------------------------------------------------------------------------------------------------\n";

			for (User user : users) {

				PrintUser(user);
				cout << endl;


			}
			cout << "--------------------------------------------------------------------------------------------------------------------\n";

			
		
	}

};

