#pragma once
#include<iostream>
#include"Client.h"
#include"Screen.h"
#include"clsInputValidate.h"
#include<string>
#include"Person.h"
#include"clsString.h"

using namespace std;
const string DELIM = "#//#";
const string FILENAMEUSERS = "UsersData.txt";

class User : public Person
{
public:
	enum PermissionOptions {
		eToShowAllClient = 1,
		eToAddClient = 2,
		eToDeleteClient = 4,
		eToUpdateClient = 8,
		eToFindClient = 16,
		eToTransactions = 32,
		eToManageUsers = 64,

		eAllPermissions = -1
	};
	enum UserMode { emptyMode = 0, updateMode = 1, AddNewMode = 2 };
	enum SaveResult { FailedEmpty = 0, SuccessFull = 1, FailedAccountExists = 2 };

private:

	string _username;
	string _password;
	int _permissionGranted;
	UserMode _mode;
	bool _markForDelete = false;


	static string ConvertUserToRecordString(User user) {

		string recordString = "";

		recordString += user._username + DELIM
			+ user._password + DELIM
			+ to_string(user._permissionGranted) + DELIM
			+ user.FirstName + DELIM
			+ user.LastName + DELIM
			+ user.Phone + DELIM
			+ user.Email;

		return recordString;


	}
	
	void SaveUserToFile(User user) {
		string fileName = "UsersData.txt";

		fstream myfile;
		myfile.open(fileName, ios::out | ios::app);

		string recordString = ConvertUserToRecordString(user);

		if (myfile.is_open()) {

			myfile << recordString << endl;
			cout << "added successfully\n";
			myfile.close();


		}


	}
	static User ConvertRecordStringToUser(string text) {

		vector<string> data = clsString::SplitString(text, DELIM);

		return User(UserMode::updateMode, data[0], data[1], stoi(data[2]), data[3], data[4], data[5], data[6]);

	}

	int ReadUserPermissions() {
		char answer;
		int permissionGranted = 0;

		cout << "\ndo you want to give the user all permissions ? [y] [n] ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			permissionGranted = PermissionOptions::eAllPermissions;
		}
		else {
			cout << "\ndo you want to give show all clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToShowAllClient;

			cout << "\ndo you want to give add clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToAddClient;

			cout << "\ndo you want to give delelte clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToDeleteClient;

			cout << "\ndo you want to give update clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToUpdateClient;

			cout << "\ndo you want to give find clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToFindClient;

			cout << "\ndo you want to give manage transactions of clients permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToTransactions;

			cout << "\ndo you want to give manage users permission ? [y] [n] ";
			cin >> answer;
			if (tolower(answer) == 'y')
				permissionGranted |= PermissionOptions::eToManageUsers;



		}
		return permissionGranted;
	}

	void ReadUserData() {

		FirstName = clsInputValidate::ReadString("enter the first name ");
		LastName = clsInputValidate::ReadString("enter the last name ");
		Phone = clsInputValidate::ReadString("enter the phone ");
		Email = clsInputValidate::ReadString("enter the email ");

		string username;
		do {
			cout << "\nenter username : ";
			getline(cin >> ws, username);
		} while (CheckUserExists(username));

		_username = username;
		_password = clsInputValidate::ReadString("enter the password ");

		_permissionGranted = ReadUserPermissions();


	}
	


	static void PrintSaveResult(SaveResult sr, User user) {

		switch (sr) {
		case(SaveResult::FailedEmpty):
			cout << "error saving , the user is empty \n";
			break;

		case(SaveResult::SuccessFull):
			cout << "success \n";
			break;

		case(SaveResult::FailedAccountExists):
			cout << "error saving , the user do already exists \n";
			break;

		}

	}
	static void SaveUpdatedUsersToFile(const vector<User>& users) {

		fstream myfile;
		string recordString;
		myfile.open(FILENAMEUSERS, ios::out);

			if (myfile.is_open())
			{
				for (User user : users) {

					if (user._markForDelete == false)
					{
						recordString = ConvertUserToRecordString(user);
						myfile << recordString << endl;
					}

				}
				myfile.close();

			}

	}


	void UpdateSystem(User user) {
		vector<User> users = UpdateUsersList(user);
		SaveUpdatedUsersToFile(users);
	}

	vector<User> UpdateUsersList(User user) {
		vector<User> users = LoadUsersFromFile();
		for (User& u : users) {
			if (u.Username == user.Username)
				u = user;
		}

		return users;
	}


	

	static vector<User> LoadUsersFromFile() {
		string fileName = "UsersData.txt";
		vector<User> users;
		User user = GetEmptyUserObject();
		fstream myfile;
		myfile.open(fileName, ios::in);
		string line;

		if (myfile.is_open()) {

			while (getline(myfile, line)) {

				if (line != "") {
					user = ConvertRecordStringToUser(line);
					users.push_back(user);
				}
			}

			myfile.close();

		}

		return users;

	}

	void ChangeUserData() {

		_username = clsInputValidate::ReadString("enter the new username ");

		while (CheckUserExists(_username)) {
			_username = clsInputValidate::ReadString("the username already exists , try another one ");
		}

		_password = clsInputValidate::ReadString("enter the new password : ");
		FirstName = clsInputValidate::ReadString("enter the new first name ");
		LastName = clsInputValidate::ReadString("enter the new last name ");
		Phone = clsInputValidate::ReadString("enter the new phone ");
		Email = clsInputValidate::ReadString("enter the new Email ");
		_permissionGranted = ReadUserPermissions();


	}

	



	//============================================================================
	//============================================================================
public:
	User(UserMode mode, string username, string password,int per, string firstName, string lastName, string phone, string email)
		: Person(firstName, lastName, phone, email) {
		_username = username;
		_password = password;
		_permissionGranted = per;
		_mode = mode;
	}

	string GetUserName()
	{
		return _username;
	}

	void SetUserName(string UserName)
	{
		_username = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string Username;

	void SetPassword(string Password)
	{
		_password = Password;
	}

	string GetPassword()
	{
		return _password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_permissionGranted = Permissions;
	}

	int GetPermissions()
	{
		return _permissionGranted;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int PermissionGranted;
	//============
	//============

	bool IsEmptyUser() {
		return _mode == UserMode::emptyMode;
	}

	static User GetEmptyUserObject() {
		return User(UserMode::emptyMode, "", "", 0, "", "", "", "");
	}


	static User GetAddNewUserObject() {
		return User(UserMode::AddNewMode, "", "", 0, "", "", "", "");
	}
	
	static vector<User> GetListOfAllUsers() {
		return LoadUsersFromFile();
	}
	

	
	static bool CheckUserExists(string userName) {

		const vector<User>& users = LoadUsersFromFile();
		for (const User& user : users) {
			if (user._username == userName)
			{
				return true;

			}
		}
		return false;


	}
	
	
	SaveResult Save() {

		
		switch(this->_mode) {

		case (UserMode::AddNewMode):
		{
			if (CheckUserExists(this->_username))
				return SaveResult::FailedAccountExists;

			SaveUserToFile(*this);
			this->_mode = UserMode::updateMode;
			return SaveResult::SuccessFull;
		}
		case (UserMode::updateMode):
		{
			UpdateSystem(*this);
			return SaveResult::SuccessFull;
		}
		case(UserMode::emptyMode):
			return SaveResult::FailedEmpty;
		
		default:
			return SaveResult::FailedEmpty;

		}
		

	}

	static void AddUser() {
		
		char answer = 'n';
		SaveResult sv;
		do {
			User user = GetAddNewUserObject();
			user.ReadUserData();
			sv = user.Save();
			PrintSaveResult(sv, user);
			user.PrintUserCard();
			cout << "do you want to add more users ? [y] [n] ";
			cin >> answer;


		} while (tolower(answer) == 'y');

	}

	
	static void UpdateUser() {
		string userName = MyLib::ReadString("enter username to update ");


		User user = GetEmptyUserObject();;
		char answer;
		user = FindUser(userName);

		while (user.IsEmptyUser())
		{
			userName = clsInputValidate::ReadString("user not found, try again (or enter x to exit)");
			if(userName == "x" || userName == "X")
				return;
			user = FindUser(userName);
		}


		user.PrintUserCard();
		cout << "are you sure you want to update this client ? [y] [n]  ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			user.ChangeUserData();
			user.Save();
		}
		else {
			cout << "user not updated \n";
		}

	}

	

	static User FindUser(string userName) {
		vector<User> users = LoadUsersFromFile();
		User user = GetEmptyUserObject();
		for (User u : users) {
			if (u._username == userName)
			{
				user = u;
				break;
			}
		}
		return user;


	}
	static User FindUser(string userName,string password) {

		vector<User> users = LoadUsersFromFile();
		User user = GetEmptyUserObject();
		for (User u : users) {
			if (u._username == userName && u._password == password)
			{
				user = u;
				break;
			}
		}
		return user;

	}

	
	void PrintUserCard() {
		cout << "---------------------------------------\n";
		cout << "username           " << " : " << _username << endl
			 << "full name          " << " : " << FullName() << endl
			 << "phone              " << " : " << Phone  << endl
			 << "email              " << " : " << Email << endl
			 << "password           " << " : " << _password << endl
			 << "permission granted " << " : " << _permissionGranted << endl;
		cout << "---------------------------------------\n";

	}

	bool Delete() {
		_markForDelete = true;
		if (Save() == SaveResult::SuccessFull) {
			*this = GetEmptyUserObject();
			return true;
		}
		else
			return false;
	}

	static void DeleteUser() {
		string userName;

		do
		{
			userName = MyLib::ReadString("enter user name to delete ");
			if (userName == "Admin")
				cout << "cannot delete this account \n";

		} while (userName == "Admin");

		char answer;
		User user = GetEmptyUserObject();
		user = FindUser(userName);

		while (user.IsEmptyUser()) {
			userName = clsInputValidate::ReadString("username doesnt exists , try again (or enter x to exit) ");
			if (userName == "x" || userName == "X")
				return;
			user = FindUser(userName);
		}

		user.PrintUserCard();
		cout << "are you sure you want to delete the account ? [y] [n] ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {

			user._markForDelete = true;
			user.Save();
		}
		else {
			cout << "\nUser not deleted\n";

		}


	}

	bool CheckHasPermission(PermissionOptions permissionToAsk) {
		if (this->PermissionGranted == PermissionOptions::eAllPermissions)
			return true;

		if ((this->PermissionGranted & permissionToAsk) == permissionToAsk)
			return true;

		return false;
	}

	 void RegisterLoginInFile() {
		string record = Date::GetCurrentDateAndTimeString() + "#//#"
			+ Username + "#//#"
			+ Password + "#//#"
			+ to_string(PermissionGranted);

		fstream myfile;
		myfile.open("LogData.txt", ios::out | ios::app);
		if (myfile.is_open()) {
			myfile << record << endl;
		}
		myfile.close();
	}

	 
	 static vector<string> GetRegisterHistoryLinesOfString() {
		 vector<string> lines;

		 fstream myfile;
		 myfile.open("LogData.txt", ios::in);
		 string line = "";
		 if (myfile.is_open()) {

			 while (getline(myfile, line)) {
				 lines.push_back(line);
			 }
			 myfile.close();
		 }

		 return lines;  

	 }
	 //TODO : create a register record struct and replace the needed parts in the code
};

