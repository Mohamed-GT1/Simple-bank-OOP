#pragma once
#include<iostream>
#include"Screen.h"
#include"Currency.h"

using namespace std;
class FindCurrencyScreen : public Screen
{
	static void PrintCurrencyCard(Currency currency) {
		cout << "==========================\n";
		cout << "country name  : " << currency.Country() << endl;
		cout << "currency code : " << currency.CurrencyCode() << endl;
		cout << "currency name : " << currency.CurrencyName() << endl;
		cout << "Rate          : " << currency.Rate() << endl;
		cout << "\n==========================\n";
	}

public:
	static void ShowFindCurrencyScreen() {
		DrawHeader("find currency Screen");

		cout << "find currency by : [1]code   [2]country\n";
		int answer = clsInputValidate::ReadIntNumberBetween(1, 2);
		Currency currency = Currency::GetEmptyCurrencyObject();

		switch (answer) {
		case 1:
			currency = Currency::FindByCode(clsInputValidate::ReadString("enter the code of the currency you wish yo update"));
			break;
		case 2:
			currency = Currency::FindByCountry(clsInputValidate::ReadString("enter the country of the currency you wish yo update"));
			break;
		}
	
		if (currency.IsEmpty()) {
			cout << "\ncurrency does not exist\n";
			return;
		}

		PrintCurrencyCard(currency);
	}
};

