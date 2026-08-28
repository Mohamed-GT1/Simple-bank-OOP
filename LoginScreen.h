#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"User.h"
#include"Global.h"
#include"MainScreen.h"
#include"Date.h"
#include<fstream>
using namespace std;

class LoginScreen : public Screen
{
private:

	
	
	static bool Login() {

		int trials = 3;
		
		do {
			
			
			string username = clsInputValidate::ReadString("enter the username : ");
			string password = clsInputValidate::ReadString("enter the password : ");
			CurrentUser = User::FindUser(username, password);

			if (CurrentUser.IsEmptyUser()) {
				cout << "invlaid username or password ! ";
				trials--;
				cout << "\nyou have " << trials << " attempts left to login before lock out \n";

				if (trials == 0) {
					cout << "\n system lockout, too many attempts to log in \n";
					return false;
				}

			}
			else {
				CurrentUser.RegisterLoginInFile();
				break;
			}

		} while (true);

		MainScreen::ShowMainMenu();
		return true;
	}

public:

	static bool ShowLoginScreen() {
		bool successLogin;
			
			DrawHeader("Login Screen");
			successLogin = Login();

			return successLogin;
	}

};

