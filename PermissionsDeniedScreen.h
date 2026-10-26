#pragma once
#include "Screen.h"

class PermissionsDeniedScreen : protected Screen
{
public:
	static void showPermissionsDeniedScreen()
	{
		string title = "Permissions Denied";
		string subTitle = "Contact your admin for help!";

		_showScreenHeader(title, subTitle);

		cout << "\a";
	}
};

