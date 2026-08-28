#pragma once
#include<iostream>
#include"Screen.h"
#include"clsInputValidate.h"
#include"Client.h"
#include"ClientListScreen.h"
#include"AddNewClientScreen.h"
#include"DeleteClientScreen.h"
#include"UpdateClientScreen.h"
#include"FindClientScreen.h"
#include"TransactionsScreen.h"
#include"ManageUsersScreen.h"
#include"Global.h"
using namespace std;

class MainScreen : Screen 
{
	enum MainMenuOptions {
		ShowAllClients = 1,
		AddNewClient,
		DeleteClient,
		UpdateClient,
		FindClient,
		TransactionsMenu,
		ManageUsersMenu,
		Logout

	};

	static void ClearScreen() {
		system("cls");
	}

	static MainMenuOptions ReadMainMenuOption(int from , int to) {
		int number = clsInputValidate::ReadIntNumberBetween(from, to);
		

		return (MainMenuOptions)number;
	}

	static void ShowAllClientsScreen() {
		ClientListScreen::ShowAllCLientsScreen();
	}
	static void ShowAddNewClientScreen() {
		AddNewClientScreen::ShowAddNewClientScreen();
	}
	static void ShowDeleteClientScreen() {
		DeleteClientScreen::ShowDeleteClientScreen();
	}
	static void ShowUpdateClientScreen() {
		UpdateClientScreen::ShowUpdateClientScreen();
	}
	static void ShowFindClientScreen() {
		FindClientScreen::ShowFindClientScreen();
	}
	static void ShowTransactionsMenuScreen() {
		TransactionsScreen::ShowTransactionMenuScreen();
	}
	static void ShowManageUsersScreen() {
		ManageUsersScreen::ShowManageUsersScreen();
	}
	static void LogUserOut() {
		CurrentUser = User::GetEmptyUserObject();
	}
	


	static void PerformMainMenuOption(MainMenuOptions option) {

		ClearScreen();

		

		switch (option) {

		case MainMenuOptions::ShowAllClients:
			if(CheckHasAccess(User::PermissionOptions::eToShowAllClient))
			ShowAllClientsScreen();
			break;

		case MainMenuOptions::AddNewClient:
			if (CheckHasAccess(User::PermissionOptions::eToAddClient))
			ShowAddNewClientScreen();
			break;
		case MainMenuOptions::DeleteClient:
			if(CheckHasAccess(User::PermissionOptions::eToDeleteClient))
			ShowDeleteClientScreen();
			break;
		case MainMenuOptions::UpdateClient:
			if (CheckHasAccess(User::PermissionOptions::eToUpdateClient))
			ShowUpdateClientScreen();
			break;
		case MainMenuOptions::FindClient:
			if (CheckHasAccess(User::PermissionOptions::eToFindClient))
			ShowFindClientScreen();
			break;
		case MainMenuOptions::TransactionsMenu: 
		{
			if (!CheckHasAccess(User::PermissionOptions::eToTransactions)) {
				cout << "\npress any key to go back . . . ";
				system("pause>nul");
			}
			else
				ShowTransactionsMenuScreen();
			return;
		}
		case MainMenuOptions::ManageUsersMenu:
		{
			if (!CheckHasAccess(User::PermissionOptions::eToManageUsers)) {
				cout << "\npress any key to go back . . . ";
				system("pause>nul");
			}
			else
				ShowManageUsersScreen();
			return;
		}
		case MainMenuOptions::Logout:
			LogUserOut();
			return;

		}

		cout << "\npress any key to go back . . . ";
		system("pause>nul");

	}

public:

	

	
	static void ShowMainMenu() {
		
		MainMenuOptions option;

		do {

			ClearScreen();
			DrawHeader("Bank System");

			cout << "=======================================\n";
			cout << "\tMAIN MENU \n";
			cout << "=======================================\n";
			cout << "\t" << "[1] Show all clients.\n";
			cout << "\t" << "[2] Add new client.\n";
			cout << "\t" << "[3] Delete client.\n";
			cout << "\t" << "[4] Update client.\n";
			cout << "\t" << "[5] Find client.\n";
			cout << "\t" << "[6] Transactions.\n";
			cout << "\t" << "[7] Manage Users.\n";
			cout << "\t" << "[8] Logout.\n";
			cout << "=======================================\n";

			 option = ReadMainMenuOption(1,8);

			PerformMainMenuOption(option);

		} while (option !=MainMenuOptions::Logout);


	}
};

