#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include"DepositScreen.h"
#include"WithdrawScreen.h"
#include"AllClientsBalanceScreen.h"
using namespace std;

class TransactionsScreen : public Screen
{
private:

public:
	enum TransactionMenu {
		Deposit = 1,
		Withdraw = 2,
		TotalBalance = 3,
		Exit = 4

	};

	
	static TransactionMenu ReadTransactionMenuOptions(int from , int to) {
		int num = clsInputValidate::ReadIntNumberBetween(from, to);
		return (TransactionMenu)num;
	}
	static void ShowDepositScreen() {
		DepositScreen::ShowDepositScreen();
	}
	static void ShowWithDrawScreen() {
		WithdrawScreen::ShowWithdrawScreen();
	}
	static void ShowTotalBalancesScreen() {
		AllClientsBalanceScreen::ShowAllClientsBalanceScreen();
	}

	static void PerformTransactionMenuOption(TransactionMenu option) {
		system("cls");

		switch (option) {
		case (TransactionMenu::Deposit):
			ShowDepositScreen();
			break;
		case (TransactionMenu::Withdraw):
			ShowWithDrawScreen();
			break;
		case(TransactionMenu::TotalBalance):
			ShowTotalBalancesScreen();
			break;
		case(TransactionMenu::Exit):
			return;
		}

		cout << "press any key to go back . . . ";
		system("pause>nul");

	}
	static void ShowTransactionMenuScreen() {
		
		TransactionMenu option;

		do {
			system("cls");
			DrawHeader("Transactions screen ");

			cout << "=======================================\n";
			cout << "\tTransaction Menu \n";
			cout << "=======================================\n";
			cout << "\t" << "[1] Deposit.\n";
			cout << "\t" << "[2] Withdraw.\n";
			cout << "\t" << "[3] Total Balances.\n";
			cout << "\t" << "[4] Exit.\n";
			cout << "=======================================\n";

			 option = ReadTransactionMenuOptions(1, 4);

			PerformTransactionMenuOption(option);
		} while (option != TransactionMenu::Exit);

	}
};

