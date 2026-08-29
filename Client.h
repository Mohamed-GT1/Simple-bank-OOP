#pragma once
#include<iostream>
#include"Person.h"
#include"clsString.h"
#include<fstream>
#include<vector>
#include<string>
#include"clsInputValidate.h"
#include"clsUtil.h"




using namespace std;
class Client : public Person
{
public:
	enum SaveResult { FailedEmpty = 0, SuccessFull = 1, FailedAccountExists = 2 };

private:
	enum ClientMode { emptyMode = 0, updateMode = 1, AddNewMode = 2 };
	

	string _accountNumber;
	string _pincode;
	double _balance;
	ClientMode _clientMode;
	bool _markForDeletion;

	

	

	static Client _ConvertRecordStringToClientObject(string line) {
		vector<string> parts = clsString::SplitString(line, "#//#");

		Client client(updateMode, parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], stod(parts[6]));

		return client;
		
	}

	static string ConvertClientToRecordString(Client client) {
		string line = "";
		line += client.FirstName+"#//#";
		line += client.LastName+"#//#";
		line += client.Phone + "#//#";
		line += client.Email+"#//#";
		line += client._accountNumber+"#//#";
		line += client._pincode+"#//#";
		line += to_string(client._balance);
		

		return line;

	}

	static vector<Client> _LoadClientsFromFile() {
		fstream myfile;
		string line = "";
		vector<Client> clients;
		
		myfile.open("ClientsData.txt", ios::in);

		if (myfile.is_open()) {

			while (getline(myfile, line)) {
				Client client = _ConvertRecordStringToClientObject(line);
				clients.push_back(client);
			}
			myfile.close();
		}

		return clients;
	}

	static Client GetEmptyClient() {
		return Client(emptyMode, "", "", "", "", "", "", 0);
	}

	void _UpdateSystem() {


		vector<Client> clients = _UpdateClientVector();


		_UpdateClientsDataInFile(clients);

	}

	void _UpdateClientsDataInFile(const vector<Client>& clients) {

		fstream myfile;

		myfile.open("ClientsData.txt", ios::out);

		if (myfile.is_open()) {

			for (const Client& c : clients) {

				if(c._markForDeletion == false)
				myfile << ConvertClientToRecordString(c) << endl;

			}
			myfile.close();

		}

	}

	vector<Client> _UpdateClientVector() {

		vector<Client> clients = _LoadClientsFromFile();

		for (Client& c : clients) {
			if (c.AccountNumber == this->AccountNumber) {
				c = *this;
			}
		}

		return clients;

	}

	static void _UpdateClientFromUser(Client& client) {
		cout << "updating client . . . \n";
		client.FirstName = clsInputValidate::ReadString("enter the first name :");
		client.LastName = clsInputValidate::ReadString("enter the last name :");
		client.Phone = clsInputValidate::ReadString("enter Phone number :");
		client.Email = clsInputValidate::ReadString("enter email :");
		client.Pincode = clsInputValidate::ReadString("enter pincode :");
		client.Balance = clsInputValidate::ReadDoubleNumber("enter Balance :");


	}

	

	
	static void _AddNewClientToFile(Client client) {
		fstream myfile;

		myfile.open("ClientsData.txt", ios::out | ios::app);

		if (myfile.is_open()) {
			myfile << ConvertClientToRecordString(client) << endl;
		}

		myfile.close();
	}

	

	void _PrintClientLine() {

		cout << left << setw(20) << FullName() << setw(2) << "|"
			<< setw(15) << AccountNumber << setw(2) << "|"
			<< setw(8) << Pincode << setw(2) << "|"
			<< setw(20) << Phone << setw(2) << "|"
			<< setw(30) << Email << setw(2) << "|"
			<< setw(15) << Balance << setw(2) << "|";


	}
	static void _PrintSaveResult(SaveResult sr, Client client) {

		switch (sr) {
		case(SaveResult::FailedEmpty):
			cout << "error saving , the client is empty \n";
			break;

		case(SaveResult::SuccessFull):
			cout << "success \n";
			client.Print();
			break;

		case(SaveResult::FailedAccountExists):
			cout << "error saving , the client do already exists \n";
			break;

		}

	}


	//==============================================================================
	//==============================================================================
	
public :
	
	bool Delete() {


		vector<Client> clients = _LoadClientsFromFile();
		bool found = false;

		for (Client& c : clients) {
			if (c.AccountNumber == this->AccountNumber) {
				c._markForDeletion = true;
				found = true;
			}
		}

		if (found == false)
			return false;

		_UpdateClientsDataInFile(clients);

		*this = GetEmptyClient();

		return true;


	}

	bool IsEmptyClient() {
		return _clientMode == ClientMode::emptyMode;
	}

	static Client _GetAddNewClientObject(string accountNumber) {
		return Client(ClientMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}

	Client(ClientMode cm, string firstName, string lastName, string phone, string email, string accountNumber, string pincode, double balance)
		:Person(firstName, lastName, phone, email)
	{
		_accountNumber = accountNumber;
		_pincode = pincode;
		_balance = balance;
		_clientMode = cm;
		_markForDeletion = false;

	}

	void SetPincode(string pincode) {
		_pincode = pincode;
	}

	string GetPincode() {
		return _pincode;
	}

	__declspec( property(get = GetPincode, put = SetPincode)) string Pincode;

	void SetBalance(double balance) {
		_balance = balance;
	}

	double GetBalance() {
		return _balance;
	}

	__declspec( property(get = GetBalance, put = SetBalance)) double Balance;

	string GetAccountNumber() {
		return _accountNumber;
	}

	__declspec( property(get = GetAccountNumber)) string AccountNumber;




	static Client FindClient(string accountNumber) {
		vector<Client> clients = _LoadClientsFromFile();
		
		for (Client c : clients) {
			if (c._accountNumber == accountNumber)
				return c;
		}

		return GetEmptyClient();

	}

	static Client FindClient(string accountNumber,string pincode) {
		vector<Client> clients = _LoadClientsFromFile();
		
		for (Client c : clients) {
			if (c._accountNumber == accountNumber && c._pincode == pincode)
				return c;
		}

		return GetEmptyClient();

	}


	void Print() override {
		cout << "=================================\n";
		cout << "first name       : " << FirstName << endl;
		cout << "Last name        : " << LastName << endl;
		cout << "full name        : " << FullName() << endl;
		cout << "phone            : " << Phone << endl;
		cout << "email            : " << Email << endl;
		cout << "Account nuumber  : " << _accountNumber << endl;
		cout << "pincode          : " << _pincode << endl;
		cout << "balance          : " << _balance << endl;
		cout << "=================================\n";
	}

	static bool DoesClientExist(string accountNumber) {
		Client c = FindClient(accountNumber);

		
		return !c.IsEmptyClient();
	}

	


	SaveResult Save() {

		 switch (_clientMode) {

		 case(ClientMode::emptyMode):
				 return SaveResult::FailedEmpty;
			 
		 case(ClientMode::updateMode):
			 _UpdateSystem();
			 return SaveResult::SuccessFull;

		 case(ClientMode::AddNewMode):
		 {
			 if (DoesClientExist(this->AccountNumber))
				 return SaveResult::FailedAccountExists;

			 _AddNewClientToFile(*this);
			 this->_clientMode = ClientMode::updateMode;
			 return SaveResult::SuccessFull;
		 }

		 default:
			 return SaveResult::FailedEmpty;
		 }

	}

	 
	static void UpdateClient() {
		string accountNumber = clsInputValidate::ReadString("enter the account number you wish to update ");
		Client client = FindClient(accountNumber);
		while (client.IsEmptyClient())
		{
			cout << "account number does not exist , choose another one \n";
			getline(cin, accountNumber);
			client = FindClient(accountNumber);
		}

		_UpdateClientFromUser(client);

		SaveResult saveResult;

		saveResult = client.Save();

		_PrintSaveResult(saveResult, client);
	}

	


	static void AddNewClient() {
		string accountNumber = clsInputValidate::ReadString("enter the account number of the client to add ");

		while (DoesClientExist(accountNumber)) {
			cout << "this account number already exists for a client , try another one \n";
				accountNumber = clsInputValidate::ReadString("enter the account number of the client to add ");
		}

		Client client = _GetAddNewClientObject(accountNumber);

		_UpdateClientFromUser(client);

		SaveResult sr = client.Save();

		_PrintSaveResult(sr,client);


	}

	

	static void DeleteClient() {
		string accountNumber = clsInputValidate::ReadString("enter the account number of the client you want to delete ");
		Client client = FindClient(accountNumber);

		while (client.IsEmptyClient()) {
			accountNumber = clsInputValidate::ReadString("account number doesnt exists , try again \nenter the account number of the client you want to delete ");
			client = FindClient(accountNumber);
		}

		client.Print();

		char answer;
		cout << "are you sure you want to delete this client ? [y] [n] ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {
			
			if (client.Delete()) {
				cout << "deleted successfully \n";
			}
			else {
				cout << "error deleting client \n";
			}
		}
		
	}

	


	static void ShowAllClients() {

		vector<Client> clients = GetAllClientsList();

		cout << "				list of (" << clients.size() << ") clients\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(20) << "Name" << setw(2) << "|" <<setw(15) << "account number" << setw(2) << "|" << setw(8) << "pincode" << setw(2) << "|"
			<< setw(20) << "phone number" << setw(2) << "|"<<setw(30) << "Email" << setw(2) << "|"
			<< setw(15) << "balance" << setw(2) << "|";
		cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";

		if (clients.size() != 0) {

			for (Client client : clients) {

				client._PrintClientLine();
				cout << endl;


			}
		}
		else {
			cout << "     there are no clients saved       \n";
		}

		cout << "-----------------------------------------------------------------------------------------------------------------------\n";

		
	}

	static vector<Client> GetAllClientsList() {

		return _LoadClientsFromFile();
	}


	static void ShowAllBalancesOfClients( ) {

		vector<Client>clients = _LoadClientsFromFile();

		cout << "				list of (" << clients.size() << ") clients\n";
		cout << "-------------------------------------------------------\n";
		cout << left << setw(15) << "account number" << setw(2) << "|"
			<< setw(20) << "Name" << setw(2) << "|"
			<< setw(15) << "balance" << setw(2) << "|";
		cout << "\n-------------------------------------------------------\n";

		double total = 0;

		for ( Client  client : clients) {
			cout << left << setw(15) << client.AccountNumber << setw(2) << "|"
				<< setw(20) << client.FullName() << setw(2) << "|"
				<< setw(15) << client.Balance << setw(2) << "|\n";
			total += client.Balance;


		}
		cout << "-------------------------------------------------------\n";
		cout << "\t\ttotal balance : " << total << " ("<<clsUtil::NumberToText(total)<<")" << endl;

	



	}

	bool Deposit(double amount) {
		Balance += amount;
		if (Save() == SaveResult::SuccessFull)
			return true;

		return false;
	}

	bool Withdraw(double amount) {
		if (amount > Balance) {
			return false;
		}
		else {
			Balance -= amount;
			if (Save() == SaveResult::SuccessFull)
				return true;

			return false;
		}
	}

	static double GetTotalBalancesOfAllClients() {
		vector<Client> clients = _LoadClientsFromFile();

		double total = 0;

		for (Client c : clients) {
			total += c.Balance;
		}

		return total;
	}

	static bool TransFromClient1ToClient2(Client &client1,Client &client2,double amount) {
		
		if (!client1.Withdraw(amount))
			return false;
		if (!client2.Deposit(amount))
			return false;


		
		return true;

	}

	static string ReadAccountNumber(string message) {
		string accountNumber = clsInputValidate::ReadString(message);
		while (!Client::DoesClientExist(accountNumber)) {
			accountNumber = clsInputValidate::ReadString("accont number doesnt exists , try again ");
		}

		return accountNumber;
	}

	struct TransferRecordObject {
		string DateAndTime;
		string accountNumberFrom;
		string accountNumberTo;
		double amount;
		double balanceFrom;
		double balanceTo;
		string user;
	};

	static string ConvertTransferRecordObjectToString(TransferRecordObject object) {
		string line = "";
		line += object.DateAndTime + "#//#"
			+ object.accountNumberFrom + "#//#"
			+ object.accountNumberTo + "#//#"
			+ to_string(object.amount) + "#//#"
			+ to_string(object.balanceFrom) + "#//#"
			+ to_string(object.balanceTo) + "#//#"
			+ object.user;

		return line;
	}

	static TransferRecordObject ConvertStringToTransferRecordObject(string line) {
		vector<string> data = clsString::SplitString(line, "#//#");
		TransferRecordObject object;
		object.DateAndTime = data[0];
		object.accountNumberFrom = data[1];
		object.accountNumberTo = data[2];
		object.amount = stod(data[3]);
		object.balanceFrom = stod(data[4]);
		object.balanceTo = stod(data[5]);
		object.user = data[6];

		return object;
	}

	 static void LogTransferRecordInFile(TransferRecordObject object) {
		 fstream myfile;

		 myfile.open("transferData.txt", ios::out | ios::app);

		 if (myfile.is_open()) {
			 myfile << ConvertTransferRecordObjectToString(object) << endl;
			 myfile.close();
		 }

	}

	 static vector<TransferRecordObject> LoadTransferRecordObjectsFromFile() {
		 fstream myfile;
		 vector<TransferRecordObject> objects;
		 string line = "";
		 myfile.open("transferData.txt", ios::in);

		 if (myfile.is_open()) {
			 while (getline(myfile, line)) {
				 objects.push_back(ConvertStringToTransferRecordObject(line));
			 }
			 myfile.close();
		 }

		 return objects;
	 }
	
};

