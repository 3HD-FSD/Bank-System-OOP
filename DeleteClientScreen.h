#pragma once
#include "Screen.h"
#include "Client.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

using namespace std;

class DeleteClientScreen : protected Screen
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
	static void showDeleteClientScreen()
	{
		string title = "Delete Client Screen";
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

		cout << "\nAre you sure you want to delete this client? Y / N ? ";
		char choice = InputValidation::readChar();

		if (toupper(choice) == 'Y')
		{
			client.markClientModeForDelete();

			Client::enSaveResults saveResult = client.save();

			switch (saveResult)
			{
			case Client::enSaveResults::SaveSuccessed:
				cout << "\nClient deleted successfully!" << endl;
				_printClientInfo(client);
				break;
			case Client::enSaveResults::SaveFaild:
				cout << "\nError account was not saved because it's Empty!" << endl;;
				break;
			case Client::enSaveResults::SaveFaildAccountNumberExists:
				cout << "\nError account number is not found!" << endl;;
				break;
			}
		}
	}
};