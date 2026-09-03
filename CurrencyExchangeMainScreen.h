#pragma once
#include<iostream>
#include"Screen.h"
#include"AllCurrenciesScreen.h"
#include"FindCurrencyScreen.h"
#include"UpdateCurrencyRateScreen.h"
#include"CurrencyCalculatorScreen.h"
using namespace std;

class CurrencyExchangeMainScreen : public Screen
{

		enum CurrencyExchangeOptions {
			ShowAllCurrencies = 1,
			FindCurrency,
			UpdateCurrencyRate,
			CurrencyCalculator,
			MainMenu,
		};

		static void ClearScreen() {
			system("cls");
		}

		static CurrencyExchangeOptions ReadCurrencyExchangeMenuOption(int from, int to) {
			int number = clsInputValidate::ReadIntNumberBetween(from, to);


			return (CurrencyExchangeOptions)number;
		}

		static void ShowAllCurrenciesScreen() {
			
			AllCurrenciesScreen::ShowAllCurrenciesScreen();
		}
		static void ShowFindCurrencyScreen() {
			FindCurrencyScreen::ShowFindCurrencyScreen();
		}
		static void ShowUpdateCurrencyRateScreen() {
			UpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
		}
		static void ShowCurrencyCalculatorScreen() {
			CurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
		}
		

		static void PerformCurrencyExchangeMenuOption(CurrencyExchangeOptions option) {

			ClearScreen();



			switch (option) {

			case CurrencyExchangeOptions::ShowAllCurrencies:
					ShowAllCurrenciesScreen();
				break;

			case CurrencyExchangeOptions::FindCurrency:
					ShowFindCurrencyScreen();
				break;
			case CurrencyExchangeOptions::UpdateCurrencyRate:
					ShowUpdateCurrencyRateScreen();
				break;
			case CurrencyExchangeOptions::CurrencyCalculator:
					ShowCurrencyCalculatorScreen();
				break;
			case CurrencyExchangeOptions::MainMenu:
				return;

			}

			cout << "\npress any key to go back . . . ";
			system("pause>nul");

		}

	public:




		static void ShowCurrencyExchangeMainScreen() {

			CurrencyExchangeOptions option;

			do {

				ClearScreen();
				DrawHeader("Currency Exchange main screen");

				cout << "=======================================\n";
				cout << "\tMAIN MENU \n";
				cout << "=======================================\n";
				cout << "\t" << "[1] Show all currencies.\n";
				cout << "\t" << "[2] Find currency.\n";
				cout << "\t" << "[3] update currency rate.\n";
				cout << "\t" << "[4] currency calculator.\n";
				cout << "\t" << "[5] Main Menu.\n";
				cout << "=======================================\n";

				option = ReadCurrencyExchangeMenuOption(1, 5);

				PerformCurrencyExchangeMenuOption(option);

			} while (option != CurrencyExchangeOptions::MainMenu);


		}
	};




