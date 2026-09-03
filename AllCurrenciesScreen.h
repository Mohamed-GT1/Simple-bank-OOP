#pragma once
#include<iostream>
#include"Currency.h"
#include"Screen.h"

using namespace std;
class AllCurrenciesScreen : public Screen
{
	static void PrintCurrency(Currency currency) {


		cout << left << setw(30) << currency.Country() << setw(2) << "|"
			<< setw(14) << currency.CurrencyCode() << setw(2) << "|"
			<< setw(35) << currency.CurrencyName() << setw(2) << "|"
			<< setw(10) << currency.Rate() << setw(2) << "|";

	}
public:
	static void ShowAllCurrenciesScreen() {
		DrawHeader("All currencies Screen");

		vector<Currency> currencies = Currency::LoadAllCurrenciesFromFile();

		cout << "				list of (" << currencies.size() << ") currency\n";
		cout << "------------------------------------------------------------------------------------------------\n";
		cout << left << setw(30) << "country" << setw(2) << "|"
			<< setw(14) << "currency code" << setw(2) << "|"
			<< setw(35) << "currency name" << setw(2) << "|"
			<< setw(10) << "Rate" << setw(2) << "|";
		cout << "\n------------------------------------------------------------------------------------------------\n";

		for (Currency currency : currencies) {

			PrintCurrency(currency);
			cout << endl;

		}
		cout << "------------------------------------------------------------------------------------------------\n";

	}
};

