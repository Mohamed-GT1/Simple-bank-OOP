#pragma once
#include<iostream>
using namespace std;

class Person
{
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;

public:
	Person(string firstName,string lastName,string phone , string email) {
		_firstName = firstName;
		_lastName = lastName;
		_phone = phone;
		_email = email;
	}

	void SetFirstName(string name) {
		_firstName = name;
	}

	string GetFirstName() {
		return _firstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName) )string FirstName;
	
	void SetLastName(string name) {
		_lastName = name;
	}

	string GetLastName() {
		return _lastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;
	
	void SetEmail(string email) {
		_email = email;
	}

	string GetEmail() {
		return _email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) string Email;
	
	void SetPhone(string phone) {
		_phone = phone;
	}

	string GetPhone() {
		return _phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	string FullName() {
		return _firstName + " " + _lastName;
	}

	void virtual Print() {
		cout << "=================================\n";
		cout << "first name : " << _firstName<<endl;
		cout << "Last name  : " << _lastName << endl;
		cout << "full name  : " << FullName() << endl;
		cout << "phone      : " << _phone << endl;
		cout << "email      : " << _email << endl;
		cout << "=================================\n";
	}

};

