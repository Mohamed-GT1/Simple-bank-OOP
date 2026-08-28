#pragma once

#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
using namespace std;

class DeleteUserScreen : public Screen
{
private:

	static void PrintSaveResult(User::SaveResult sr, User user) {

		switch (sr) {
		case(User::SaveResult::FailedEmpty):
			cout << "error saving , the user is empty \n";
			break;

		case(User::SaveResult::SuccessFull):
			cout << "success \n";
			break;

		case(User::SaveResult::FailedAccountExists):
			cout << "error saving , the user do already exists \n";
			break;

		}

	}
	static void PrintUserCard(User user) {
		cout << "---------------------------------------\n";
		cout << "username           " << " : " << user.Username << endl
			<< "full name          " << " : " << user.FullName() << endl
			<< "phone              " << " : " << user.Phone << endl
			<< "email              " << " : " << user.Email << endl
			<< "password           " << " : " << user.Password << endl
			<< "permission granted " << " : " << user.PermissionGranted << endl;
		cout << "---------------------------------------\n";

	}
public:

	static void ShowDeleteUserScreen() {
		DrawHeader("Delete user screen");

		string userName;

		do
		{
			userName = MyLib::ReadString("enter user name to delete ");
			if (userName == "Admin")
				cout << "cannot delete this account \n";

		} while (userName == "Admin");

		char answer;
		User user = User::GetEmptyUserObject();
		user = User::FindUser(userName);

		while (user.IsEmptyUser()) {
			userName = clsInputValidate::ReadString("username doesnt exists , try again (or enter x to exit) ");
			if (userName == "x" || userName == "X")
				return;
			user = User::FindUser(userName);
		}

		user.PrintUserCard();
		cout << "are you sure you want to delete the account ? [y] [n] ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {

			if (user.Delete()) {
				cout << "\nsuccessfully deleted the user \n";
				PrintUserCard(user);
			}
			else
				cout << "\nerror deleting the user\n";
		}
		else {
			cout << "\nUser not deleted\n";

		}

	}
};

