#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"
#include "String.h"

class Client : public Person
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewClientMode = 2, DeleteClientMode = 3 };

	enMode _mode;
	string _accountNumber;
	string _pinCode;
	float _balance;
	bool _markForDelete = false;

	static Client _convertLineToClientObject(string line, string seperator = ",")
	{
		vector<string> vClientData = String::split(line, seperator);

		enMode mode = enMode::UpdateMode;
		string firstName = vClientData[0];
		string lastName = vClientData[1];
		string phone = vClientData[2];
		string email = vClientData[3];
		string accountNumber = vClientData[4];
		string pinCode = vClientData[5];
		float balance = stof(vClientData[6]);

		return Client(mode, firstName, lastName, phone, email, accountNumber, pinCode, balance);
	}

	static string _convertClientObjectToLine(Client client, string seperator = ",")
	{
		string strClientData = "";

		strClientData += client.firstName + seperator;
		strClientData += client.lastName + seperator;
		strClientData += client.phone + seperator;
		strClientData += client.email + seperator;
		strClientData += client._accountNumber + seperator;
		strClientData += client.pinCode + seperator;
		strClientData += to_string(client.balance);

		return strClientData;
	}

	static Client _getEmptyClientObject()
	{
		return Client(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<Client> _loadClientsDataFromFile()
	{
		vector<Client> vClients;

		fstream file;
		file.open("clients.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Client client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}
			file.close();
		}
		return vClients;
	}

	void _saveClientsDataInFile(vector<Client>& vClients)
	{
		fstream file;
		file.open("clients.txt", ios::out);
		if (file.is_open())
		{
			string line;
			for (Client& client : vClients)
			{
				if (!(client._markForDelete))
				{
					line = _convertClientObjectToLine(client);
					file << line << endl;
				}
			}
			file.close();
		}
	}

	void _addClientDataInFile(Client client)
	{
		fstream file;
		file.open("clients.txt", ios::out | ios::app);
		if (file.is_open())
		{
			string line = _convertClientObjectToLine(client);
			file << line << endl;
			file.close();
		}
	}




	void _update()
	{
		vector<Client> vClients;

		vClients = _loadClientsDataFromFile();

		for (Client& client : vClients)
		{
			if (_accountNumber == client._accountNumber)
			{
				client = *this;
				break;
			}
		}

		_saveClientsDataInFile(vClients);
	}

	void _add()
	{
		_addClientDataInFile(*this);
	}

	void _delete()
	{
		vector<Client> vClients = _loadClientsDataFromFile();
		for (Client& client : vClients)
		{
			if (_accountNumber == client._accountNumber)
			{
				client._markForDelete = true;
				break;
			}
		}
		_saveClientsDataInFile(vClients);
		*this = _getEmptyClientObject();
	}

public:
	Client(enMode mode, string firstName, string lastName, string phone, string email, string accountNumber, string pinCode, float balance) : Person(firstName, lastName, phone, email)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_balance = balance;
	}

	string getAccountNumber()
	{
		return _accountNumber;
	}

	void setPinCode(string pinCode)
	{
		_pinCode = pinCode;
	}

	string getPinCode()
	{
		return _pinCode;
	}

	__declspec(property(put = setPinCode, get = getPinCode)) string pinCode;

	void setBalance(float balance)
	{
		_balance = balance;
	}

	float getBalance()
	{
		return _balance;
	}

	__declspec(property(put = setBalance, get = getBalance)) float balance;






	bool isEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	static Client find(string accountNumber)
	{
		fstream file;
		file.open("clients.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Client client = _convertLineToClientObject(line);
				if (accountNumber == client.getAccountNumber())
				{
					file.close();
					return client;
				}
			}
			file.close();
		}
		return _getEmptyClientObject();
	}

	static Client find(string accountNumber, string pinCode)
	{
		fstream file;
		file.open("clients.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Client client = _convertLineToClientObject(line);
				if (accountNumber == client.getAccountNumber() && pinCode == client.pinCode)
				{
					file.close();
					return client;
				}
			}
		}
		return _getEmptyClientObject();
	}

	static bool isClientExist(string accountNumber)
	{
		return !(find(accountNumber).isEmpty());
	}



	static Client getAddNewClientObject(string accountNumber)
	{
		return Client(enMode::AddNewClientMode, "", "", "", "", accountNumber, "", 0);
	}

	void markClientModeForDelete()
	{
		_mode = enMode::DeleteClientMode;
	}

	static vector<Client> getClientsList()
	{
		return _loadClientsDataFromFile();
	}

	static float getTotalBalance()
	{
		vector<Client> vClients = getClientsList();
		float totalBalance = 0;
		for (Client client : vClients)
			totalBalance += client.balance;
		return totalBalance;
	}

	enum enDepositResults { DepositFaildInvalidAmount, DepositFaildAmountBiggerThanMaxAmount, DepositSuccessed };

	enDepositResults deposit(float amount)
	{
		if (amount <= 0)
		{
			return enDepositResults::DepositFaildInvalidAmount;
		}
		else if (amount > 1000000)
		{
			return enDepositResults::DepositFaildAmountBiggerThanMaxAmount;
		}
		else
		{
			_balance += amount;
			save();
			return enDepositResults::DepositSuccessed;
		}
	}

	enum enWithdrawResults { WithdrawFaildInvalidAmount, WithdrawFaildAmountBiggerThanBalance, WithdrawSuccessed };

	enWithdrawResults withdraw(float amount)
	{
		if (amount <= 0)
		{
			return enWithdrawResults::WithdrawFaildInvalidAmount;
		}
		else if (amount > balance)
		{
			return enWithdrawResults::WithdrawFaildAmountBiggerThanBalance;
		}
		else
		{
			_balance -= amount;
			save();
			return enWithdrawResults::WithdrawSuccessed;
		}
	}

	enum enTransferResults { TransferFaildInvalidAmount, TransferFaildAmountBiggerThanBalance, TransferSuccessed };

	enTransferResults transfer(Client& clientToTransferTo, float amount, string userName)
	{
		if (amount <= 0)
		{
			return enTransferResults::TransferFaildInvalidAmount;
		}
		else if (amount > balance)
		{
			return enTransferResults::TransferFaildAmountBiggerThanBalance;
		}
		else
		{
			withdraw(amount);
			clientToTransferTo.deposit(amount);
			_transferLog(clientToTransferTo, amount, userName);
			return enTransferResults::TransferSuccessed;
		}
	}

	enum enSaveResults { SaveFaild, SaveSuccessed, SaveFaildAccountNumberExists, SaveFaildAccountNumberNotFound };

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::SaveFaild;
		case enMode::UpdateMode:
			_update();
			return enSaveResults::SaveSuccessed;
		case enMode::AddNewClientMode:
			if (isClientExist(_accountNumber))
			{
				return enSaveResults::SaveFaildAccountNumberExists;
			}
			else
			{
				_add();
				return enSaveResults::SaveSuccessed;
			}
		case enMode::DeleteClientMode:
			if (!isClientExist(_accountNumber))
			{
				return enSaveResults::SaveFaildAccountNumberNotFound;
			}
			else
			{
				_delete();
				return enSaveResults::SaveSuccessed;
			}
		}
	}

	void _transferLog(Client& clientToTransferTo, float amount, string userName)
	{
		fstream file;
		file.open("transferLogs.txt", ios::out | ios::app);

		if (file.is_open())
		{
			string line;
			line = Date::dateToString(Date::getSystemDate()) + " - " + Date::timeToString(Date::getSystemTime()) + "," + _accountNumber + "," + clientToTransferTo.getAccountNumber() + "," + to_string(amount) + "," + to_string(balance) + "," + to_string(clientToTransferTo.balance) + "," + userName;
			if (line != "")
			{
				file << line << endl;
			}
			file.close();
		}
	}

	struct stTransferLog
	{
		string dateAndTime;
		string sourceAccountNumber;
		string DestinationAccountNumber;
		float amount;
		float sourceClientBalance;
		float destinationClientBalance;
		string userName;
	};

	static vector<stTransferLog> getTransferLogsList()
	{
		vector<stTransferLog> vTransferLogsList;

		fstream file;
		file.open("transferLogs.txt", ios::in);

		if (file.is_open())
		{
			string line;
			stTransferLog transferLog;

			while (getline(file, line))
			{
				if (line != "")
				{
					transferLog = _convertLineToTransferLogStruct(line);
					vTransferLogsList.push_back(transferLog);
				}
			}
			file.close();
		}

		return vTransferLogsList;
	}

private:
	static stTransferLog _convertLineToTransferLogStruct(string line, string seperator = ",")
	{
		stTransferLog transferLog;

		vector<string> transferLogData = String::split(line, seperator);

		transferLog.dateAndTime = transferLogData[0];
		transferLog.sourceAccountNumber = transferLogData[1];
		transferLog.DestinationAccountNumber = transferLogData[2];
		transferLog.amount = stof(transferLogData[3]);
		transferLog.sourceClientBalance = stof(transferLogData[4]);
		transferLog.destinationClientBalance = stof(transferLogData[5]);
		transferLog.userName = transferLogData[6];

		return transferLog;
	}
};