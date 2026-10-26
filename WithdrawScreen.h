#pragma once
#include "Screen.h"
#include "Client.h"

class WithdrawScreen : protected Screen
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
	static void showWithdrawScreen()
	{
		string title = "Withdraw Screen";

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

		cout << "\nEnter an amount for withdraw : ";
		float amount = InputValidation::readFloatNumber();

		cout << "\nAre you sure you want to perform this transaction? Y / N ? ";
		char choice = InputValidation::readChar();

		if (toupper(choice) == 'Y')
		{
			Client::enWithdrawResults withdraeResult = client.withdraw(amount);
			switch (withdraeResult)
			{
			case Client::enWithdrawResults::WithdrawFaildInvalidAmount:
				cout << "\nInvalid amount, amount is negative or zero!" << endl;
				break;
			case Client::enWithdrawResults::WithdrawFaildAmountBiggerThanBalance:
				cout << "\nInvalid amount, amount is more than balance!" << endl;
				cout << "\nYour balance is : " << client.balance << " $" << endl;
				break;
			case Client::enWithdrawResults::WithdrawSuccessed:
				cout << "\nAmount withdrawed successfully!" << endl;
				cout << "\nNew balance is : " << client.balance << " $" << endl;
				break;
			}
		}
		else
		{
			cout << "\nOperation was cancelled!" << endl;
		}
	}
};