#pragma once
#include<iostream>
#include<string>
#include"clsString.h"
#include<vector>
#include<fstream>
#include<iomanip>
#include"clsInputValidate.h"
using namespace std;

class Currency
{
public:
	enum CurrencyMode {
		UpdateMode,EmptyMode
	};
private:

	CurrencyMode mode;
	string country;
	string currencyCode;
	string currencyName;
	double rate;

	
public:
	Currency(CurrencyMode mode,string country ,string currencyCode,string currencyName,double rate) {
		this->mode = mode;
		this->country = country;
		this->currencyCode = currencyCode;
		this->rate = rate;
	}
	string Country() {
		return country;
	}
	string CurrencyCode() {
		return currencyCode;
	}
	string CurrencyName() {
		return currencyName;
	}
	double Rate() {
		return rate;
	}

	bool UpdateRate(double newRate) {
		if (newRate < 0)
			return false;

		rate = newRate;
		UpdateSystem();
		return true;
		
	}

	static string ConvertCurrencyToString(Currency currency) {
		string line = "";
		string delim = "#//#";
		line += currency.Country() + delim
			+ currency.CurrencyCode() + delim
			+ currency.CurrencyName() + delim
			+ to_string(currency.rate);

		return line;

	}

	static Currency GetEmptyCurrencyObject() {
		return Currency(CurrencyMode::EmptyMode, "", "", "", 0);
	}

	static Currency ConvertStringToCurrency(string line) {
		vector<string> data = clsString::SplitString(line, "#//#");
		Currency currency = GetEmptyCurrencyObject();
		currency.mode = UpdateMode;
		currency.country = data[0];
		currency.currencyCode = data[1];
		currency.currencyName = data[2];
		currency.rate = stod(data[3]);

		return currency;

	}

	static vector<Currency> LoadAllCurrenciesFromFile() {
		fstream myfile;
		vector<Currency> currencies;
		Currency currency = GetEmptyCurrencyObject();
		myfile.open("Currencies.txt", ios::in);
		string line = "";

		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				currency = ConvertStringToCurrency(line);
				currencies.push_back(currency);
			}
			myfile.close();
		}

		return currencies;
	}

	static Currency FindByCode(string code) {
		vector<Currency> currencies = LoadAllCurrenciesFromFile();

		for (Currency currency : currencies) {
			if (currency.CurrencyCode() == clsString::StringToUpperCase(code)) {
				return currency;
			}
		}

		return GetEmptyCurrencyObject();
	}

	static Currency FindByCountry(string country) {
		
		vector<Currency> currencies = LoadAllCurrenciesFromFile();

		for (Currency currency : currencies) {
			if (clsString::StringToUpperCase(currency.Country()) == clsString::StringToUpperCase(country)) {
				return currency;
			}
		}

		return GetEmptyCurrencyObject();
	}

	 void PrintCurrencyCard() {
		cout << "==========================\n";
		cout << "country name  : " << country<<endl;
		cout << "currency code : " << currencyCode<<endl;
		cout << "currency name : " << currencyName<<endl;
		cout << "Rate          : " << rate<<endl;
		cout << "\n==========================\n";
	}

	 void UpdateNewCurrenciesInFile(vector<Currency> currencies) {
		 fstream myfile;
		 myfile.open("Currencies.txt", ios::out);
		

		 if (myfile.is_open()) {
			 for (Currency currency : currencies) {
				 myfile << ConvertCurrencyToString(currency) << endl;
			 }
			 myfile.close();
		 }

	 }

	 void UpdateSystem() {
		 vector<Currency> currencies = LoadAllCurrenciesFromFile();
		 for (Currency& currency : currencies) {
			 if (currency.currencyCode == this->currencyCode)
				 currency = *this;
		 }
		 UpdateNewCurrenciesInFile(currencies);

	 }

	 static void UpdateCurrencyRate() {
		 cout << "dow do you want to search for the currency ? by code[1] by country [2]\n";
		 int answer = clsInputValidate::ReadIntNumberBetween(1, 2);
		 Currency currency = GetEmptyCurrencyObject();

		 switch (answer) {
		 case 1:
			  currency = FindByCode(clsInputValidate::ReadString("enter the code of the currency you wish yo update"));
			 break;
		 case 2:
			  currency = FindByCountry(clsInputValidate::ReadString("enter the country of the currency you wish yo update"));
			 break;
		 }

		 currency.PrintCurrencyCard();

		 double newRate = clsInputValidate::ReadDoubleNumber("enter the new rate you wish to update to");
		 if (!currency.UpdateRate(newRate)) {
			 cout << "\ninvalid rate , didnt update\n";
			 return;
		 }

		 
		 cout << "\nsuccessful\n"; 
		 currency.PrintCurrencyCard();
		 
	 }

	  bool IsEmpty() {
		  return mode == CurrencyMode::EmptyMode;
	 }

	  static bool DoesCurrencyExist(string currencyCode) {
		  
		  Currency currency = FindByCode(currencyCode);
		  return !(currency.IsEmpty());
	  }
	
};

