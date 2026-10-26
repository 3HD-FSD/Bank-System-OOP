#pragma once

#include "Screen.h"
#include "Client.h"
#include <iostream>
#include <string>

using namespace std;

class ClientsListScreen : protected Screen
{
private:
	static void _showClientData(Client& client)
	{
		cout << "|" << Util::formatString(16, client.getAccountNumber(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(10, client.pinCode, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(21, client.getFullName(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(17, client.email, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(14, client.phone, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(15, to_string(client.balance), Util::enAlign::CENTER) << "|" << endl;;
	}

public:
	static void showClientsListScreen()
	{
		vector<Client> vClients = Client::getClientsList();

		string title = "Clients List Screen";
		string subTitle = "(" + to_string(vClients.size()) + ") Client(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(1) << Util::characters('-', 110) << endl;

		cout << Util::tabs(1) <<  "|" << "    #    ";
		cout << "|" << " Account Number ";
		cout << "|" << " PIN Code ";
		cout << "|" << "      Full Name      ";
		cout << "|" << "      Email      ";
		cout << "|" << " Phone Number ";
		cout << "|" << "  Balance ($)  " << "|" << endl;
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
		if (vClients.size() == 0)
		{
			cout << Util::tabs(1) << "|" << Util::formatString(108, "No clients available in the bank.", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (Client& client : vClients)
			{
				cout << Util::tabs(1) << "|" << Util::formatString(9, to_string(++count), Util::enAlign::CENTER);
				_showClientData(client);
			}
		}
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
	}
};