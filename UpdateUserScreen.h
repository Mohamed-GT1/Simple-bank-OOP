#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
using namespace std;

class UpdateUserScreen : public Screen
{

private:

	static int ReadUserPermissions() {
		char answer;
		int permissionGranted = 0;

		cout << "\ndo you want to give the user all permissions ? [y] [n] ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			permissionGranted = User::PermissionOptions::eAllPermissions;
		}
		else {
			cout << "\ndo you want to give show all clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToShowAllClient;

			cout << "\ndo you want to give add clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToAddClient;

			cout << "\ndo you want to give delelte clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToDeleteClient;

			cout << "\ndo you want to give update clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToUpdateClient;

			cout << "\ndo you want to give find clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToFindClient;

			cout << "\ndo you want to give manage transactions of clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToTransactions;

			cout << "\ndo you want to give manage users permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= User::PermissionOptions::eToManageUsers;



		}
		return permissionGranted;
	}

	static void ReadUserData(User& user) {

		user.FirstName = clsInputValidate::ReadString("enter the first name ");
		user.LastName = clsInputValidate::ReadString("enter the last name ");
		user.Password = clsInputValidate::ReadString("enter the password ");
		user.Phone = clsInputValidate::ReadString("enter the phone ");
		user.Email = clsInputValidate::ReadString("enter the email ");


		user.PermissionGranted = ReadUserPermissions();

	}

	static void PrintSaveResult(User::SaveResult sr,User user) {

		switch (sr) {
		case(User::SaveResult::FailedEmpty):
			cout << "error saving , the user is empty \n";
			break;

		case(User::SaveResult::SuccessFull):
			cout << "successfully updated \n";
			PrintUserCard(user);
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

	static void ShowUpdateUserScreen() {
		DrawHeader("Update user Screen");

		string userName = clsInputValidate::ReadString("enter username to update ");


		User user = User::GetEmptyUserObject();;
		char answer;

		while (!User::CheckUserExists(userName))
		{
			userName = clsInputValidate::ReadString("user not found, try again (or enter x to exit)");
			if (userName == "x" || userName == "X")
				return;
		}

		user = User::FindUser(userName);
		PrintUserCard(user);
		cout << "are you sure you want to update this client ? [y] [n]  ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			ReadUserData(user);
			User::SaveResult sv = user.Save();
			PrintSaveResult(sv,user);
		}
		else {
			cout << "user not updated \n";
		}

	}
};

