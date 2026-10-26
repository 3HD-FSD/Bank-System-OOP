#pragma once
#include "Screen.h"
#include "User.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

class AddUserScreen : protected Screen
{
private:
	static void _printUserInfo(User& user)
	{
		cout << "\User Data\n";
		cout << "------------------------------" << endl;
		cout << "FirstName      : " << user.firstName << endl;
		cout << "LastName       : " << user.lastName << endl;
		cout << "Phone          : " << user.phone << endl;
		cout << "Email          : " << user.email << endl;
		cout << "Username       : " << user.getUserName() << endl;
		cout << "Password       : " << user.password << endl;
		cout << "Permissions    : " << to_string(user.permissions) << endl;
		cout << "------------------------------" << endl;
	}

	static int _readPermissions()
	{
		cout << "\nDo you want to give this user full access? Y / N ? ";
		char choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");

		if (toupper(choice) == 'Y')
		{
			return -1;
		}
		else
		{
			int permissions = 0;
			cout << "\nDo you want to give user access to :" << endl;
			
			cout << "\nShow clients list ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::ClientsList;
			}

			cout << "\nAdd Client ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::AddClient;
			}

			cout << "\nDelete Client ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::DeleteClient;
			}

			cout << "\nUpdate Client ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::UpdateClient;
			}

			cout << "\nFind Client ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::FindClient;
			}

			cout << "\nMake Transactions ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::Transactions;
			}

			cout << "\nManage Users ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::Users;
			}

			cout << "\nShow Login Registers List ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::LoginRegistersList;
			}

			cout << "\nCurrency Exchange ? Y / N ? ";
			choice = InputValidation::readYesOrNo("Invalid character, enter y or n : ");
			if (toupper(choice) == 'Y')
			{
				permissions += User::enPermissions::CurrencyExchange;
			}

			return permissions;
		}
	}

	static void _readUserInfo(User& user)
	{
		cout << "Enter first Name : ";
		user.firstName = InputValidation::readString();
		cout << "Enter last Name : ";
		user.lastName = InputValidation::readString();
		cout << "Enter phone : ";
		user.phone = InputValidation::readString();
		cout << "Enter email : ";
		user.email = InputValidation::readEmail("@gmail.com");
		cout << "Enter password : ";
		user.password = InputValidation::readString();
		user.permissions = _readPermissions();
	}
public:
	static void showAddUserScreen()
	{
		string title = "Add User Screen";

		_showScreenHeader(title);

		cout << "Enter a username : ";
		string userName = InputValidation::readString();

		while (User::isUserExist(userName))
		{
			cout << "Username is already exist, please enter another username : ";
			userName = InputValidation::readString();
		}

		User user = User::getAddNewUserObject(userName);

		_readUserInfo(user);

		User::enSaveResults saveResult = user.save();

		switch (saveResult)
		{
		case User::enSaveResults::SaveSuccessed:
			cout << "\nUser added successfully!" << endl;
			_printUserInfo(user);
			break;
		case User::enSaveResults::SaveFaild:
			cout << "\nError user was not saved because it's Empty!" << endl;;
			break;
		case User::enSaveResults::SaveFaildUserNameExists:
			cout << "\nError username is already exist!" << endl;;
			break;
		}
	}
};