#pragma once
#include "Screen.h"
#include "User.h"
#include "InputValidation.h"
#include "Util.h"
#include <iostream>
#include <string>

class FindUserScreen : protected Screen
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
	static void showFindUserScreen()
	{
		string title = "Find Usre Screen";
		_showScreenHeader(title);

		cout << "Enter a user : ";
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
			cout << "\nYou can not access to the admin data!" << endl;
			return;
		}

		_printUserInfo(user);
	}
};

