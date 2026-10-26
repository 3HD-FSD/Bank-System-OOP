#pragma once
#include "Screen.h"
#include "User.h"
#include <iostream>
#include <string>

class UsersListScreen : protected Screen
{
private:
	static void _showUserData(User& user)
	{
		cout << "|" << Util::formatString(14, user.getUserName(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(10, user.password, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(21, user.getFullName(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(21, user.email, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(14, user.phone, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(13, to_string(user.permissions), Util::enAlign::CENTER) << "|" << endl;;
	}

public:
	static void showUsersListScreen()
	{
		vector<User> vUsers = User::getUsersList();

		string title = "Users List Screen";
		string subTitle = "(" + to_string(vUsers.size()) + ") User(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(1) << Util::characters('-', 110) << endl;

		cout << Util::tabs(1) << "|" << "    #    ";
		cout << "|" << "   Username   ";
		cout << "|" << " Password ";
		cout << "|" << "      Full Name      ";
		cout << "|" << "        Email        ";
		cout << "|" << " Phone Number ";
		cout << "|" << " Permissions " << "|" << endl;
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
		if (vUsers.size() == 0)
		{
			cout << Util::tabs(1) << "|" << Util::formatString(108, "No users available in the system.", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (User& user : vUsers)
			{
				if (user.getUserName() == "admin" && currentUser.getUserName() != "admin")
				{
					continue;
				}
				cout << Util::tabs(1) << "|" << Util::formatString(9, to_string(++count), Util::enAlign::CENTER);
				_showUserData(user);
			}
		}
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
	}
};