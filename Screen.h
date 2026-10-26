#pragma once
#include <iostream>
#include <string>
#include "Util.h"
#include "Global.h"
#include "Date.h"

using namespace std;

class Screen
{
protected:
	static void _showScreenHeader(string title, string subTitle = "")
	{
		cout << Util::tabs(5) << Util::characters('-', 40) << endl;
		cout << Util::tabs(5) << Util::formatString(40, title, Util::enAlign::CENTER) << endl;
		if (subTitle != "")
		{
			cout << Util::tabs(5) << Util::formatString(40, subTitle, Util::enAlign::CENTER) << endl;
		}
		cout << Util::tabs(5) << Util::characters('-', 40) << endl;

		cout << endl;
		cout << Util::tabs(5) << "User : " << currentUser.getUserName() << endl;
		cout << Util::tabs(5) << "Date : " << Date::dateToString(Date::getSystemDate()) << endl;
		cout << endl;
	}
};

