#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
using namespace std;

class FindUserScreen : public Screen
{
private:
	static void PrintUserCard(User user) {
		cout << "---------------------------------------\n";
		cout<< "username           " << " : " << user.Username << endl
			<< "first name         " << " : " << user.FirstName << endl
			<< "last name          " << " : " << user.LastName << endl
			<< "full name          " << " : " << user.FullName() << endl
			<< "phone              " << " : " << user.Phone << endl
			<< "email              " << " : " << user.Email << endl
			<< "password           " << " : " << user.Password << endl
			<< "permission granted " << " : " << user.PermissionGranted << endl;
		cout << "---------------------------------------\n";

	}
public:
	static void ShowFindUserScreen() {
		DrawHeader("find user screen ");

		User user = User::GetEmptyUserObject();
		string username = clsInputValidate::ReadString("enter the username of the user you want to find ");
		user = User::FindUser(username);
		while (user.IsEmptyUser()) {
			username = clsInputValidate::ReadString("username doesnt exists, try again ");
			user = User::FindUser(username);
		}

		PrintUserCard(user);
	}
};

