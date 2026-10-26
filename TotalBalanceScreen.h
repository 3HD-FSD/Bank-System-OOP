#pragma once
#include "Screen.h"
#include "Client.h"

class TotalBalanceScreen : protected Screen
{
private:
	static void _printClientDataAndBalance(Client& client)
	{
		cout << "|" << Util::formatString(16, client.getAccountNumber(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(21, client.getFullName(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(15, to_string(client.balance), Util::enAlign::CENTER) << "|" << endl;
	}
public:
	static void showBalancesListAndTotalBalanceScreen()
	{
		vector<Client> vClients = Client::getClientsList();

		string title = "Total Balance Screen";
		string subTitle = "(" + to_string(vClients.size()) + ") Client(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(3) << Util::characters('-', 66) << endl;
		cout << Util::tabs(3) << "|" << "    #    ";
		cout << "|" << " Account Number ";
		cout << "|" << "      Full Name      ";
		cout << "|" << "  Balance ($)  " << "|" << endl;
		cout << Util::tabs(3) << Util::characters('-', 66) << endl;

		if (vClients.size() == 0)
		{
			cout << Util::tabs(3) << "|" << Util::formatString(64, "No clients available in the Bank", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (Client& client : vClients)
			{
				cout << Util::tabs(3) << "|" << Util::formatString(9, to_string(++count), Util::enAlign::CENTER);
				_printClientDataAndBalance(client);
			}
			cout << Util::tabs(3) << Util::characters('-', 66) << endl;
			cout << Util::tabs(3) << "|" << Util::formatString(64, "Total Balance = " + to_string(Client::getTotalBalance()) + " $", Util::enAlign::CENTER) << "|" << endl;
		}
		cout << Util::tabs(3) << Util::characters('-', 66) << endl;
	}
};