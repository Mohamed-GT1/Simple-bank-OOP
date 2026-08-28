#pragma once
#include<iostream>
#include"User.h"
#include"Global.h"
using namespace std;

class Screen
{

protected:

	

	static void DrawHeader(string title,string subtitle="") {
		
			cout << "======================================================================================================\n";
			cout << "\t\t\t\t\t " << title;
			if (subtitle != "")
				cout << "\n\t\t\t\t\t " << subtitle;
			cout << "\n======================================================================================================\n\n\n";
	}

	static void ShowAccessDenied() {
		system("cls");
		cout << "======================================================================================================\n";
		cout << "\t\t\t Access Denied , you dont have the permission to view this";
		cout << "\n======================================================================================================\n\n\n";
		
		
	}

	static bool CheckHasAccess(User::PermissionOptions permissionToAsk) {
		bool hasAccess = CurrentUser.CheckHasPermission(permissionToAsk);
		if (!hasAccess) {
			ShowAccessDenied();
			return false;
		}
		
		return true;

		
	}
public:

	

};

