#include<iostream>
#include"Person.h"
#include"Client.h"
#include"MainScreen.h"
#include"User.h"
#include"LoginScreen.h"
#include"Global.h"

using namespace std;

int main() {
	
	//MainScreen::ShowMainMenu();
	while (true) {
		LoginScreen::ShowLoginScreen();
	}
	

	return 0;
}