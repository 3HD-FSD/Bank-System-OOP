#pragma once
#include "Screen.h"
#include "Client.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

using namespace std;


class AddClientScreen : protected Screen
{
private:
	static void _printClientInfo(Client &client)
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
	static void _readClientInfo(Client& client)
	{
		cout << "Enter first Name : ";
		client.firstName = InputValidation::readString();
		cout << "Enter last Name : ";
		client.lastName = InputValidation::readString();
		cout << "Enter phone : ";
		client.phone = InputValidation::readString();
		cout << "Enter email : ";
		client.email = InputValidation::readEmail("@gmail.com");
		cout << "Enter PIN code : ";
		client.pinCode = InputValidation::readString();
		cout << "Enter balance : ";
		client.balance = InputValidation::readFloatNumber();
	}
public:
	static void showAddClientScreen()
	{
		string title = "Add Client Screen";

		_showScreenHeader(title);

		cout << "Enter a account number : ";
		string accountNumber = InputValidation::readString();

		while (Client::isClientExist(accountNumber))
		{
			cout << "Account number is already exist, please enter another account number : ";
			accountNumber = InputValidation::readString();
		}

		Client client = Client::getAddNewClientObject(accountNumber);

		_readClientInfo(client);

		Client::enSaveResults saveResult = client.save();

		switch (saveResult)
		{
		case Client::enSaveResults::SaveSuccessed:
			cout << "\nClient added successfully!" << endl;
			_printClientInfo(client);
			break;
		case Client::enSaveResults::SaveFaild:
			cout << "\nError account was not saved because it's Empty!" << endl;;
			break;
		case Client::enSaveResults::SaveFaildAccountNumberExists:
			cout << "\nError account number is already exist!" << endl;;
			break;
		}
	}
};