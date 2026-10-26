#pragma once
#include "Screen.h"
#include "InputValidation.h"
#include "DepositScreen.h"
#include "WithdrawScreen.h"
#include "TransferScreen.h"
#include "TransferLogScreen.h"
#include "TotalBalanceScreen.h"

class TransactionsScreen : protected Screen
{
private:
    enum enTransactionsMenuOption
    {
        Deposit = 1,
        Withdraw = 2,
        Transfer = 3,
        TransferLogs = 4,
        TotalBalance = 5,
        Exit = 6
    };

    static void _goBackToTransactionsMenu()
    {
        cout << "\n" << Util::tabs(5) << "Press [Enter] key to go back to transactions menu...";
        system("pause>0");
        showTransactionsScreen();
    }

    static enTransactionsMenuOption _readTransactionsMenuOption()
    {
        cout << Util::tabs(5) << "Choose any service [1 -> 6] : ";
        enTransactionsMenuOption choice = enTransactionsMenuOption(InputValidation::readIntNumberBetween(1, 6, "Invalid input, choose any service [1 -> 6] : "));
        return choice;
    }

    static void _showDepositScreen()
    {
        DepositScreen::showDepositScreen();
    }

    static void _showWithdrawScreen()
    {
        WithdrawScreen::showWithdrawScreen();
    }

    static void _showTransferScreen()
    {
        TransferScreen::showTransferScreen();
    }

    static void _showTransferLogsScreen()
    {
        TransferLogScreen::showTransferLogScreen();
    }

    static void _showTotalBalanceScreen()
    {
        TotalBalanceScreen::showBalancesListAndTotalBalanceScreen();
    }

    static void _performTransactionsMenuOption(enTransactionsMenuOption choice)
    {
        switch (choice)
        {
        case enTransactionsMenuOption::Deposit:
            system("cls");
            _showDepositScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOption::Withdraw:
            system("cls");
            _showWithdrawScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOption::Transfer:
            system("cls");
            _showTransferScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOption::TransferLogs:
            system("cls");
            _showTransferLogsScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOption::TotalBalance:
            system("cls");
            _showTotalBalanceScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOption::Exit:
            break;
        default:
            cout << "Error!" << endl;
            break;
        }
    }

    static void _showTransactionsMenuOptions()
    {
        system("cls");
        _showScreenHeader("Transactions Menu Screen");

        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << Util::formatString(38, "Transactions Management", Util::enAlign::CENTER) << "|" << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << "    [1] Deposit"       << Util::formatString(24, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [2] Withdraw"      << Util::formatString(23, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [3] Transfer"      << Util::formatString(23, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [4] Transfer Logs" << Util::formatString(18, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [5] Total Balance" << Util::formatString(18, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [6] Exit"          << Util::formatString(27, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
    }

public:
    static void showTransactionsScreen()
    {
        _showTransactionsMenuOptions();
        _performTransactionsMenuOption(_readTransactionsMenuOption());
    }
};