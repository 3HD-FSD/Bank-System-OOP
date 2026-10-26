#pragma once
#include "Screen.h"
#include "User.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

class DeleteUserScreen : protected Screen
{
private:
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
public:
	static void showDeleteUserScreen()
	{
		string title = "Delete User Screen";
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

		if (userName == "admin")
		{
			cout << "\nYou can not delete the admin user!" << endl;
			return;
		}

		_printUserInfo(user);

		cout << "\nAre you sure you want to delete this user? Y / N ? ";
		char choice = InputValidation::readYesOrNo("Invalid choice, enter y or n : ");

		if (toupper(choice) == 'Y')
		{
			user.markUserModeForDelete();

			User::enSaveResults saveResult = user.save();

			switch (saveResult)
			{
			case User::enSaveResults::SaveSuccessed:
				cout << "\nUser deleted successfully!" << endl;
				_printUserInfo(user);
				break;
			case User::enSaveResults::SaveFaild:
				cout << "\nError user was not saved because it's Empty!" << endl;;
				break;
			case User::enSaveResults::SaveFaildUserNameExists:
				cout << "\nError username is not found!" << endl;;
				break;
			}
		}
	}
};

