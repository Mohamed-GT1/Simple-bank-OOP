#pragma once
#include<iostream>
#include"Screen.h"
#include"Currency.h"
#include"clsInputValidate.h"

using namespace std;

class CurrencyCalculatorScreen : public Screen
{
	static Currency ReadCurrencyFromUser(string message) {
		cout << message ;
		string code = clsInputValidate::ReadString("");

		while (!Currency::DoesCurrencyExist(code)) {
			code = clsInputValidate::ReadString("currency does not exist , try again");
		}

		return Currency::FindByCode(code);
	}
	static void PrintCurrencyCard(Currency currency) {
		cout << "==========================\n";
		cout << "country name  : " << currency.Country() << endl;
		cout << "currency code : " << currency.CurrencyCode() << endl;
		cout << "currency name : " << currency.CurrencyName() << endl;
		cout << "Rate          : " << currency.Rate() << endl;
		cout << "==========================\n\n";
	}

	static void CalculateAndPrintResults(Currency currency1,Currency currency2 , double amount) {
		double amountInUSD = currency1.ConvertToUSD(amount);
		double amountInOtherCurrency = currency1.ConvertToOtherCurrency(amount, currency2);

		cout << "\nFrom " << amount << " " << currency1.CurrencyCode() << " to USD : ";
		cout << amountInUSD << " USD\n";

		if (!(currency2.CurrencyCode() == "USD"))
			cout << "From " << amountInUSD << " USD" << " to " << currency2.CurrencyCode() << " : " << amountInOtherCurrency << " " << currency2.CurrencyCode();

	}

public:

	static void ShowCurrencyCalculatorScreen() {
		char answer = 'y';

		while (answer == 'y' || answer == 'Y') {
			system("cls");

			DrawHeader("exchange currency screen");

			Currency currency1 = ReadCurrencyFromUser("enter the currency code to exchange from");
			PrintCurrencyCard(currency1);
			cout << endl;

			Currency currency2 = ReadCurrencyFromUser("enter the currency code to exchange to");
			PrintCurrencyCard(currency2);
			cout << endl;

			double amount = clsInputValidate::ReadDoubleNumber("enter the amount to exchange ");


			CalculateAndPrintResults(currency1, currency2, amount);
			
			answer = clsInputValidate::ReadChar("\ndo you want to perfrom another operation ? [y] [n]");
		}
	}
};

