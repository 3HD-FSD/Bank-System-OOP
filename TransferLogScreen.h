#pragma once
#include "Screen.h"
#include "User.h"
#include <iostream>
#include <string>

class TransferLogScreen : protected Screen
{
private:
	static void _showTransferLogData(Client::stTransferLog& transferLog)
	{
		cout << "|" << Util::formatString(22, transferLog.dateAndTime, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(10, transferLog.sourceAccountNumber, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(10, transferLog.DestinationAccountNumber, Util::enAlign::CENTER);
		cout << "|" << Util::formatString(12, to_string(transferLog.amount), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(13, to_string(transferLog.sourceClientBalance), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(13, to_string(transferLog.destinationClientBalance), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(12, transferLog.userName, Util::enAlign::CENTER) << "|" << endl;

	}
public:
	static void showTransferLogScreen()
	{
		vector<Client::stTransferLog> vTransferLogs = Client::getTransferLogsList();

		string title = "Transfer Log List Screen";
		string subTitle = "(" + to_string(vTransferLogs.size()) + ") Record(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(1) << Util::characters('-', 110) << endl;

		cout << Util::tabs(1) << "|" << "    #    ";
		cout << "|" << "       Date/Time      ";
		cout << "|" << "  S Acc.  ";
		cout << "|" << "  D Acc.  ";
		cout << "|" << "   Amount   ";
		cout << "|" << "  S Balance  ";
		cout << "|" << "  D Balance  ";
		cout << "|" << "    User    " << "|" << endl;
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
		if (vTransferLogs.size() == 0)
		{
			cout << Util::tabs(1) << "|" << Util::formatString(108, "No transfer logs have recorded in the system.", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (Client::stTransferLog& transferLog : vTransferLogs)
			{
				if (transferLog.userName == "admin" && currentUser.getUserName() != "admin")
				{
					continue;
				}
				cout << Util::tabs(1) << "|" << Util::formatString(9, to_string(++count), Util::enAlign::CENTER);
				_showTransferLogData(transferLog);
			}
		}
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
	}
};