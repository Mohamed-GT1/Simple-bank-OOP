#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
#include"Global.h"
#include"MainScreen.h"
using namespace std;

class LoginScreen : public Screen
{
private:

	static void Login() {
		
		do {
			
			
			string username = clsInputValidate::ReadString("enter the username : ");
			string password = clsInputValidate::ReadString("enter the password : ");
			CurrentUser = User::FindUser(username, password);

			if (CurrentUser.IsEmptyUser())
				cout << "invlaid username or password ! try again ";
			else
				break;

		} while (true);

		MainScreen::ShowMainMenu();
	}

public:

	static void ShowLoginScreen() {
		
			
			DrawHeader("Login Screen");
			Login();
		
	}

};

