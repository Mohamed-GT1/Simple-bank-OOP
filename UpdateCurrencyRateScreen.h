#pragma once
#include<iostream>
#include"Screen.h"
#include"Currency.h"

using namespace std;
class UpdateCurrencyRateScreen : public Screen
{

public:
	static void ShowUpdateCurrencyRateScreen() {
		DrawHeader("update currency rate screen");

		cout << "find currency by: [1]code  [2]country\n";
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

		currency.PrintCurrencyCard();
		
		double newRate = clsInputValidate::ReadDoubleNumber("enter the new rate you wish to update to");

		char answer2 = clsInputValidate::ReadChar("are you sure you want to update this currency ? [y] [n]");
		if (answer2 == 'n' || answer2 == 'N')
		{
			cout << "currency was not updated \n";
			return;
		}

		if (!currency.UpdateRate(newRate)) {
			cout << "\ninvalid rate , didnt update\n";
			return;
		}


		cout << "\nsuccessful\n";
		currency.PrintCurrencyCard();
	}
};

