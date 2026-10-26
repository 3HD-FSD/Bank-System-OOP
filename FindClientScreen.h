#pragma once
#include "Screen.h"
#include "Client.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

using namespace std;

class FindClientScreen : protected Screen
{
private:
	static void _printClientInfo(Client& client)
	{
		cout << "\nClient Data\n";
		cout << "------------------------------" << endl;
		cout << "FirstName      : " << client.firstName << endl;
		cout << "LastName       : " << client.lastName << endl;
		cout << "Phone          : " << client.phone << endl;
		cout << "Email          : " << client.email << endl;
		cout << "Account Number : " << client.getAccountNumber() << endl;
		cout << "PIN Code       : " << client.pinCode << endl;
		cout << "Balance        : " << to_string(client.balance) << endl;
		cout << "------------------------------" << endl;
	}
public:
	static void showFindClientScreen()
	{
		string title = "Find Client Screen";
		_showScreenHeader(title);

		cout << "Enter a account number : ";
		string accountNumber = InputValidation::readString();

		Client client = Client::find(accountNumber);

		while (client.isEmpty())
		{
			cout << "Client with account number is not found, please enter another account number : ";
			accountNumber = InputValidation::readString();
			client = Client::find(accountNumber);
		}

		_printClientInfo(client);
	}
};