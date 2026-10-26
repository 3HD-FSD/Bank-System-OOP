#pragma once
#include "Screen.h"
#include "User.h"

class LoginRegisterScreen : protected Screen
{
private:
	static void _showLoginRegisterData(User::stLoginRegister& loginRegister)
	{
		cout << "|" << Util::formatString(30, loginRegister.dateAndTime, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(22, loginRegister.userName, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(22, loginRegister.password, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(21, to_string(loginRegister.permissions), Util::enAlign::CENTER) << "|" << endl;;
	}
public:
	static void showLoginRegisterScreen()
	{
		vector<User::stLoginRegister> vLoginRegisters = User::getLoginRegistersList();

		string title = "Login Registers List Screen";
		string subTitle = "(" + to_string(vLoginRegisters.size()) + ") Record(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(1) << Util::characters('-', 110) << endl;

		cout << Util::tabs(1) << "|" << "    #    ";
		cout << "|" << "           Date/Time          ";
		cout << "|" << "       Username       ";
		cout << "|" << "       Password       ";
		cout << "|" << "     Permissions     " << "|" << endl;
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
		if (vLoginRegisters.size() == 0)
		{
			cout << Util::tabs(1) << "|" << Util::formatString(108, "No login registers have recorded in the system.", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (User::stLoginRegister& loginRegister : vLoginRegisters)
			{
				if (loginRegister.userName == "admin" && currentUser.getUserName() != "admin")
				{
					continue;
				}
				cout << Util::tabs(1) << "|" << Util::formatString(9, to_string(++count), Util::enAlign::CENTER);
				_showLoginRegisterData(loginRegister);
			}
		}
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
	}
};