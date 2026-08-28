#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"AllUsersScreen.h"
#include"AddNewUserScreen.h"
#include"DeleteUserScreen.h"
#include"UpdateUserScreen.h"
#include"FindUserScreen.h"

using namespace std;

class ManageUsersScreen : public Screen
{
private:
	enum ManageUsersMenuOptions {
		eListUsers = 1,
		eAddUser = 2,
		eDeleteUser = 3,
		eUpdateUser = 4,
		eFindUser = 5,
		eMainMenu = 6
	};

	static ManageUsersMenuOptions ReadManageUsersMenuOption() {
		int num = clsInputValidate::ReadIntNumberBetween(1, 6);

		return (ManageUsersMenuOptions)num;
	}

	static void ShowAllUsersScreen() {
		AllUsersScreen::ShowAllUsersScreen();
	}
	static void ShowAddUsersScreen() {
		AddNewUserScreen::ShowAddNewUSerScreen();
	}

	static void ShowDeleteUserScreen() {
		DeleteUserScreen::ShowDeleteUserScreen();
	}

	static void ShowUpdateUserScreen() {
		UpdateUserScreen::ShowUpdateUserScreen();
	}

	static void ShowFindAndPrintUserScreen() {
		FindUserScreen::ShowFindUserScreen();
	}
	static void PerformManageUsersMenuOption(ManageUsersMenuOptions option) {

			system("cls");

			switch (option) {

			case ManageUsersMenuOptions::eListUsers:
				ShowAllUsersScreen();
				break;
			case ManageUsersMenuOptions::eAddUser:
				ShowAddUsersScreen();
				break;
			case ManageUsersMenuOptions::eDeleteUser:
				ShowDeleteUserScreen();
				break;
			case ManageUsersMenuOptions::eUpdateUser:
				ShowUpdateUserScreen();
				break;
			case ManageUsersMenuOptions::eFindUser:
				ShowFindAndPrintUserScreen();
				break;
			case ManageUsersMenuOptions::eMainMenu:
				return;

			}

			cout << "\npress any key to continue\n";
			system("pause>nul");
	}

public:

	static void ShowManageUsersScreen() {

		ManageUsersMenuOptions option;

		do {
			system("cls");
			DrawHeader("Manage users screen");

			cout << "=======================================\n";
			cout << "\tManager Users Menu \n";
			cout << "=======================================\n";
			cout << "\t" << "[1] Show all Users.\n";
			cout << "\t" << "[2] Add user.\n";
			cout << "\t" << "[3] Delete user.\n";
			cout << "\t" << "[4] Update User.\n";
			cout << "\t" << "[5] Find User.\n";
			cout << "\t" << "[6] main menu.\n";
			cout << "=======================================\n";

			option = ReadManageUsersMenuOption();
			PerformManageUsersMenuOption(option);

			

		} while (option != ManageUsersMenuOptions::eMainMenu);
	}

};

