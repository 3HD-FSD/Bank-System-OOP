#pragma once
#include "Screen.h"
#include "Client.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

class UpdateUserScreen : protected Screen
{
private:
	enum enUpdateType {
		FirstName = 1,
		LastName = 2,
		Phone = 3,
		Email = 4,
		Password = 5,
		Permissions = 6,
		All = 7,
		NoOne = 8
	};

	static void _printUserInfo(User& user)
	{
		cout << "\nUser Data\n";
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

	static void _readUserInfo(User& user, enUpdateType updateType)
	{
		if (updateType == enUpdateType::FirstName || updateType == enUpdateType::All)
		{
			cout << "Enter first Name : ";
			user.firstName = InputValidation::readString();
		}
		if (updateType == enUpdateType::LastName || updateType == enUpdateType::All)
		{
			cout << "Enter last Name : ";
			user.lastName = InputValidation::readString();
		}
		if (updateType == enUpdateType::Phone || updateType == enUpdateType::All)
		{
			cout << "Enter phone : ";
			user.phone = InputValidation::readString();
		}
		if (updateType == enUpdateType::Email || updateType == enUpdateType::All)
		{
			cout << "Enter email : ";
			user.email = InputValidation::readEmail("@gmail.com");
		}
		if (updateType == enUpdateType::Password || updateType == enUpdateType::All)
		{
			cout << "Enter password : ";
			user.password = InputValidation::readString();
		}
		if (updateType == enUpdateType::Permissions || updateType == enUpdateType::All)
		{
			user.permissions = _readPermissions();
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
		cout << "    [5] Password" << endl;
		cout << "    [6] Permissions" << endl;
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
	static void showUpdateUserScreen()
	{
		string title = "Update User Screen";
		_showScreenHeader(title);

		cout << "Enter a username : ";
		string userName = InputValidation::readString();

		User user = User::find(userName);

		while (user.isEmpty())
		{
			cout << "User with username is not found, please enter another username : ";
			userName = InputValidation::readString();
			user = User::find(userName);
		}

		if (userName == "admin" && currentUser.getUserName() != "admin")
		{
			cout << "\nYou can not update the admin user!" << endl;
			return;
		}

		_printUserInfo(user);

		_showUpdateTypes();
		enUpdateType updateType = _readUpdateType();

		if (updateType == enUpdateType::NoOne)
		{
			return;
		}

		cout << "\nUpdate User Info";
		cout << "\n------------------------------\n";
		_readUserInfo(user, updateType);

		User::enSaveResults saveResult = user.save();

		switch (saveResult)
		{
		case User::enSaveResults::SaveSuccessed:
			cout << "\nUser updated successfully!" << endl;
			_printUserInfo(user);
			break;
		case User::enSaveResults::SaveFaild:
			cout << "\nError user was not saved because it's Empty!" << endl;;
			break;
		}
	}
};

