#pragma once
#include "Screen.h"
#include "Client.h"

class TransferScreen : protected Screen
{
private:
	static void _printClientInfo(Client& client)
	{
		cout << "\nClient Data\n";
		cout << "------------------------------" << endl;
		cout << "FirstName      : " << client.firstName << endl;
		cout << "LastName       : " << client.lastName << endl;
		cout << "Account Number : " << client.getAccountNumber() << endl;
		cout << "Balance        : " << to_string(client.balance) << endl;
		cout << "------------------------------" << endl << endl;
	}
	static float _readAmountToTransfer(Client& clientToTransferFrom)
	{
		cout << "\nEnter an amount for transfer : ";
		float amount = InputValidation::readFloatNumber();

		while (amount > clientToTransferFrom.balance)
		{
			cout << "\nAmount exceeded the available balance, enter another amount : ";
			amount = InputValidation::readFloatNumber();
		}

		return amount;
	}
public:
	static void showTransferScreen()
	{
		string title = "Transfer Screen";

		_showScreenHeader(title);

		string accountNumber;

		cout << "Enter a account number to transfer from : ";
		accountNumber = InputValidation::readString();

		Client clientToTransferFrom = Client::find(accountNumber);

		while (clientToTransferFrom.isEmpty())
		{
			cout << "Client with account number is not found, please enter another account number : ";
			accountNumber = InputValidation::readString();
			clientToTransferFrom = Client::find(accountNumber);
		}

		_printClientInfo(clientToTransferFrom);

		cout << "Enter a account number to transfer to : ";
		accountNumber = InputValidation::readString();

		Client clientToTransferTo = Client::find(accountNumber);

		while (clientToTransferTo.isEmpty())
		{
			cout << "Client with account number is not found, please enter another account number : ";
			accountNumber = InputValidation::readString();
			clientToTransferTo = Client::find(accountNumber);
		}

		_printClientInfo(clientToTransferTo);

		float amount = _readAmountToTransfer(clientToTransferFrom);

		cout << "\nAre you sure you want to perform this transaction? Y / N ? ";
		char choice = InputValidation::readChar();

		if (toupper(choice) == 'Y')
		{
			Client::enTransferResults transferResult = clientToTransferFrom.transfer(clientToTransferTo, amount, currentUser.getUserName());
			switch (transferResult)
			{
			case Client::enTransferResults::TransferFaildInvalidAmount:
				cout << "\nInvalid amount, amount is negative or zero!" << endl;
				break;
			case Client::enTransferResults::TransferFaildAmountBiggerThanBalance:
				cout << "\nInvalid amount, amount is more than balance!" << endl;
				break;
			case Client::enTransferResults::TransferSuccessed:
				cout << "\nAmount deposited successfully!" << endl;
				_printClientInfo(clientToTransferFrom);
				_printClientInfo(clientToTransferTo);
				break;
			}
		}
		else
		{
			cout << "\nOperation was cancelled!" << endl;
		}
	}
};