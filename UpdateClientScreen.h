#pragma once
#include "Screen.h"
#include "Client.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

using namespace std;

class UpdateClientScreen : protected Screen
{
private:
	enum enUpdateType {
		FirstName = 1,
		LastName = 2,
		Phone = 3,
		Email = 4,
		PinCode = 5,
		Balance = 6,
		All = 7,
		NoOne = 8
	};

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

	static void _readClientInfo(Client& client, enUpdateType updateType)
	{
		if (updateType == enUpdateType::FirstName || updateType == enUpdateType::All)
		{
			cout << "Enter first Name : ";
			client.firstName = InputValidation::readString();
		}
		if (updateType == enUpdateType::LastName || updateType == enUpdateType::All)
		{
			cout << "Enter last Name : ";
			client.lastName = InputValidation::readString();
		}
		if (updateType == enUpdateType::Phone || updateType == enUpdateType::All)
		{
			cout << "Enter phone : ";
			client.phone = InputValidation::readString();
		}
		if (updateType == enUpdateType::Email || updateType == enUpdateType::All)
		{
			cout << "Enter email : ";
			client.email = InputValidation::readEmail("@gmail.com");
		}
		if (updateType == enUpdateType::PinCode || updateType == enUpdateType::All)
		{
			cout << "Enter PIN code : ";
			client.pinCode = InputValidation::readString();
		}
		if (updateType == enUpdateType::Balance || updateType == enUpdateType::All)
		{
			cout << "Enter balance : ";
			client.balance = InputValidation::readFloatNumber();
		}
	}

	static void _showUpdateTypes()
	{
		cout << "\nUpdate Types\n";
		cout << "------------------------------" << endl;
		cout << "    [1] FirstName" << endl;
		cout << "    [2] LastName" << endl;
		cout << "    [3] Phone" << endl;
		cout << "    [4] Email" << endl;
		cout << "    [5] PIN Code" << endl;
		cout << "    [6] Balance" << endl;
		cout << "    [7] All" << endl;
		cout << "    [8] No One" << endl;
		cout << "------------------------------" << endl;
	}

	static enUpdateType _readUpdateType()
	{
		cout << "Choose any type [1 -> 8] : ";
		enUpdateType choice = (enUpdateType)InputValidation::readIntNumberBetween(1, 8, "Invalid input, choose any service [1 -> 8] : ");
		return choice;
	}

public:
	static void showUpdateClientScreen()
	{
		string title = "Update Client Screen";
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

		_showUpdateTypes();
		enUpdateType updateType = _readUpdateType();

		if (updateType == enUpdateType::NoOne)
		{
			return;
		}

		cout << "\nUpdate Client Info";
		cout << "\n------------------------------\n";
		_readClientInfo(client, updateType);

		Client::enSaveResults saveResult = client.save();

		switch (saveResult)
		{
		case Client::enSaveResults::SaveSuccessed:
			cout << "\nClient updated successfully!" << endl;
			_printClientInfo(client);
			break;
		case Client::enSaveResults::SaveFaild:
			cout << "\nError account was not saved because it's Empty!" << endl;;
			break;
		}
	}
};