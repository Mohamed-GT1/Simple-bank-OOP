#include<iostream>
#include"Person.h"
#include"Client.h"
#include"MainScreen.h"
#include"User.h"
#include"LoginScreen.h"
#include"Global.h"
#include<ctime>
#include"Date.h"

using namespace std;

int main() {

	bool notlockout = true;
	//MainScreen::ShowMainMenu();
	do{
		notlockout = LoginScreen::ShowLoginScreen();

	} while (notlockout);
	

	//User::ConvertToEncryption();

	return 0;
}