#include<iostream>
#include"Person.h"
#include"Client.h"
#include"MainScreen.h"
#include"User.h"
#include"LoginScreen.h"
#include"Global.h"
#include<ctime>
#include"Date.h"
#include"Currency.h"

using namespace std;

int main() {

	/*bool notlockout = true;
	
	do{
		notlockout = LoginScreen::ShowLoginScreen();

	} while (notlockout);*/
	
	Currency::ShowAllCurrencies();

	Currency currency = Currency::FindByCode(clsInputValidate::ReadString("enter the country to find"));
	currency.PrintCurrencyCard();
	Currency::UpdateCurrencyRate();

	return 0;
}