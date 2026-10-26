#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"
#include "String.h"
#include "Date.h"

class User : public Person
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewUserMode = 2, DeleteUserMode = 3 };

	enMode _mode;
	string _userName;
	string _password;
	int _permissions;
	bool _markForDelete = false;

	static User _convertLineToUserObject(string line, string seperator = ",")
	{
		vector<string> vUserData = String::split(line, seperator);

		enMode mode = enMode::UpdateMode;
		string firstName = vUserData[0];
		string lastName = vUserData[1];
		string phone = vUserData[2];
		string email = vUserData[3];
		string userName = vUserData[4];
		string password = Util::decrypt(vUserData[5], userName.length());
		int permissions = stoi(vUserData[6]);

		return User(mode, firstName, lastName, phone, email, userName, password, permissions);
	}

	static string _convertUserObjectToLine(User user, string seperator = ",")
	{
		string strUserData = "";

		strUserData += user.firstName + seperator;
		strUserData += user.lastName + seperator;
		strUserData += user.phone + seperator;
		strUserData += user.email + seperator;
		strUserData += user._userName + seperator;
		strUserData += Util::encrypt(user.password, user.getUserName().length()) + seperator;
		strUserData += to_string(user.permissions);

		return strUserData;
	}

	static User _getEmptyUserObject()
	{
		return User(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<User> _loadUsersDataFromFile()
	{
		vector<User> vUsers;

		fstream file;
		file.open("users.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				User user = _convertLineToUserObject(line);
				vUsers.push_back(user);
			}
			file.close();
		}
		return vUsers;
	}

	void _saveUsersDataInFile(vector<User> vUsers)
	{
		fstream file;
		file.open("users.txt", ios::out);
		if (file.is_open())
		{
			string line;
			for (User& user : vUsers)
			{
				if (!(user._markForDelete))
				{
					line = _convertUserObjectToLine(user);
					file << line << endl;
				}
			}
			file.close();
		}
	}

	void _addUserDataInFile(User user)
	{
		fstream file;
		file.open("users.txt", ios::out | ios::app);
		if (file.is_open())
		{
			string line = _convertUserObjectToLine(user);
			file << line << endl;
			file.close();
		}
	}




	void _update()
	{
		vector<User> vUsers;

		vUsers = _loadUsersDataFromFile();

		for (User& user : vUsers)
		{
			if (_userName == user._userName)
			{
				user = *this;
				break;
			}
		}

		_saveUsersDataInFile(vUsers);
	}

	void _add()
	{
		_addUserDataInFile(*this);
	}

	void _delete()
	{
		vector<User> vUsers = _loadUsersDataFromFile();
		for (User& user : vUsers)
		{
			if (_userName == user._userName)
			{
				user._markForDelete = true;
				break;
			}
		}
		_saveUsersDataInFile(vUsers);
		*this = _getEmptyUserObject();
	}

public:
	enum enPermissions {
		ClientsList = 1,
		AddClient = 2,
		DeleteClient = 4,
		UpdateClient = 8,
		FindClient = 16,
		Transactions = 32,
		Users = 64,
		LoginRegistersList = 128,
		CurrencyExchange = 256
	};

	User(enMode mode, string firstName, string lastName, string phone, string email, string userName, string password, int permissions) : Person(firstName, lastName, phone, email)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_permissions = permissions;
	}

	string getUserName()
	{
		return _userName;
	}

	void setPassword(string password)
	{
		_password = password;
	}

	string getPassword()
	{
		return _password;
	}

	__declspec(property(put = setPassword, get = getPassword)) string password;

	void setPermissions(int permissions)
	{
		_permissions = permissions;
	}

	int getPermissions()
	{
		return _permissions;
	}

	__declspec(property(put = setPermissions, get = getPermissions)) int permissions;






	bool isEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	static User find(string userName)
	{
		fstream file;
		file.open("users.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				User user = _convertLineToUserObject(line);
				if (userName == user.getUserName())
				{
					file.close();
					return user;
				}
			}
			file.close();
		}
		return _getEmptyUserObject();
	}

	static User find(string userName, string password)
	{
		fstream file;
		file.open("users.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				User user = _convertLineToUserObject(line);
				if (userName == user.getUserName() && password == user.password)
				{
					file.close();
					return user;
				}
			}
		}
		return _getEmptyUserObject();
	}

	static bool isUserExist(string userName)
	{
		return !(find(userName).isEmpty());
	}



	static User getAddNewUserObject(string userName)
	{
		return User(enMode::AddNewUserMode, "", "", "", "", userName, "", 0);
	}

	void markUserModeForDelete()
	{
		_mode = enMode::DeleteUserMode;
	}

	static vector<User> getUsersList()
	{
		return _loadUsersDataFromFile();
	}

	enum enSaveResults { SaveFaild, SaveSuccessed, SaveFaildUserNameExists, SaveFaildUserNameNotFound };

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::SaveFaild;
		case enMode::UpdateMode:
			_update();
			return enSaveResults::SaveSuccessed;
		case enMode::AddNewUserMode:
			if (isUserExist(_userName))
			{
				return enSaveResults::SaveFaildUserNameExists;
			}
			else
			{
				_add();
				return enSaveResults::SaveSuccessed;
			}
		case enMode::DeleteUserMode:
			if (!isUserExist(_userName))
			{
				return enSaveResults::SaveFaildUserNameNotFound;
			}
			else
			{
				_delete();
				return enSaveResults::SaveSuccessed;
			}
		}
	}

	bool hasPermission(enPermissions permission)
	{
		return (permissions & permission) == permission;
	}

	void registerLogin()
	{
		fstream file;
		file.open("logins.txt", ios::out | ios::app);

		if (file.is_open())
		{
			string line;
			line = Date::dateToString(Date::getSystemDate()) + " - " + Date::timeToString(Date::getSystemTime()) + "," + _userName + "," + password + "," + to_string(permissions);
			if (line != "")
			{
				file << line << endl;
			}
			file.close();
		}
	}




	struct stLoginRegister
	{
		string dateAndTime;
		string userName;
		string password;
		int permissions;
	};

	static vector<stLoginRegister> getLoginRegistersList()
	{
		vector<stLoginRegister> vLoginRegistersList;

		fstream file;
		file.open("logins.txt", ios::in);

		if (file.is_open())
		{
			string line;
			stLoginRegister loginRegister;

			while (getline(file, line))
			{
				if (line != "")
				{
					loginRegister = _convertLineToLoginRegisterStruct(line);
					vLoginRegistersList.push_back(loginRegister);
				}
			}
			file.close();
		}

		return vLoginRegistersList;
	}

private:
	static stLoginRegister _convertLineToLoginRegisterStruct(string line, string seperator = ",")
	{
		stLoginRegister loginRegister;

		vector<string> loginRegisterData = String::split(line, seperator);

		loginRegister.dateAndTime = loginRegisterData[0];
		loginRegister.userName = loginRegisterData[1];
		loginRegister.password = loginRegisterData[2];
		loginRegister.permissions = stoi(loginRegisterData[3]);

		return loginRegister;
	}
};