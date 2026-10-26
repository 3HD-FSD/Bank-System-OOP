#pragma once
#include "Screen.h"
#include "InputValidation.h"
#include "ClientsListScreen.h"
#include "AddClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"
#include "FindClientScreen.h"
#include "TransactionsScreen.h"
#include "UsersScreen.h"
#include "LoginRegisterScreen.h"
#include "CurrencyExchangeScreen.h"
#include "PermissionsDeniedScreen.h"

class MainScreen : protected Screen
{
private:
    enum enMainMenuOption
    {
        ClientsList = 1,
        AddClient = 2,
        DeleteClient = 3,
        UpdateClient = 4,
        FindClient = 5,
        Transactions = 6,
        Users = 7,
        LoginRegistersList = 8,
        CurrencyExchange = 9,
        Logout = 10
    };

    static void _goBackToMainMenu()
    {
        cout << "\n" << Util::tabs(5) << "Press [Enter] key to go back to main menu...";
        system("pause>0");
        showMainScreen();
    }

    static enMainMenuOption _readMainMenuOption()
    {
        cout << Util::tabs(5) << "Choose any service [1 -> 10] : ";
        enMainMenuOption choice = enMainMenuOption(InputValidation::readIntNumberBetween(1, 10, Util::tabs(5) + "Invalid input, choose any service [1 -> 10] : "));
        return choice;
    }

    static void _showClientsListScreen()
    {
        ClientsListScreen::showClientsListScreen();
    }

    static void _showAddClientScreen()
    {
        AddClientScreen::showAddClientScreen();
    }

    static void _showDeleteClientScreen()
    {
        DeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen()
    {
        UpdateClientScreen::showUpdateClientScreen();
    }

    static void _showFindClientScreen()
    {
        FindClientScreen::showFindClientScreen();
    }

    static void _showTransactionsScreen()
    {
        TransactionsScreen::showTransactionsScreen();
    }

    static void _showUsersScreen()
    {
        UsersScreen::showUsersScreen();
    }

    static void _showLoginRegisterScreen()
    {
        LoginRegisterScreen::showLoginRegisterScreen();
    }

    static void _showCurrencyExchangeScreen()
    {
        CurrencyExchangeScreen::showCurrencyExchangeScreen();
    }

    static void _showLogoutScreen()
    {
        system("cls");
        currentUser = User::find("", "");
    }

    static void _showPermissionsDeniedScreen()
    {
        PermissionsDeniedScreen::showPermissionsDeniedScreen();
    }

    static void _showScreen(void(*screen)())
    {
        system("cls");
        screen();
        _goBackToMainMenu();
    }

    static void _performMainMenuOption(enMainMenuOption choice)
    {
        switch (choice)
        {
        case enMainMenuOption::ClientsList:
            if (currentUser.hasPermission(User::enPermissions::ClientsList))
                _showScreen(_showClientsListScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::AddClient:
            if (currentUser.hasPermission(User::enPermissions::AddClient))
                _showScreen(_showAddClientScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::DeleteClient:
            if (currentUser.hasPermission(User::enPermissions::DeleteClient))
                _showScreen(_showDeleteClientScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::UpdateClient:
            if (currentUser.hasPermission(User::enPermissions::UpdateClient))
                _showScreen(_showUpdateClientScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::FindClient:
            if (currentUser.hasPermission(User::enPermissions::FindClient))
                _showScreen(_showFindClientScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::Transactions:
            if (currentUser.hasPermission(User::enPermissions::Transactions))
                _showScreen(_showTransactionsScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::Users:
            if (currentUser.hasPermission(User::enPermissions::Users))
                _showScreen(_showUsersScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::LoginRegistersList:
            if (currentUser.hasPermission(User::enPermissions::LoginRegistersList))
                _showScreen(_showLoginRegisterScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::CurrencyExchange:
            if (currentUser.hasPermission(User::enPermissions::CurrencyExchange))
                _showScreen(_showCurrencyExchangeScreen);
            else
                _showScreen(_showPermissionsDeniedScreen);
            break;
        case enMainMenuOption::Logout:
            _showLogoutScreen();
            break;
        default:
            cout << "Error!" << endl;
            break;
        }
    }

    static void _showMainMenuOptions()
    {
        system("cls");
        _showScreenHeader("Main Screen");

        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << Util::formatString(38, "Bank Management", Util::enAlign::CENTER) << "|" << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << "    [1] Clients List"         << Util::formatString(19, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [2] Add New Client"       << Util::formatString(17, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [3] Delete Client"        << Util::formatString(18, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [4] Update Client Data"   << Util::formatString(13, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [5] Find Client"          << Util::formatString(20, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [6] Transactions"         << Util::formatString(19, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [7] Users"                << Util::formatString(26, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [8] Login Registers List" << Util::formatString(11, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [9] Currency Exchange"    << Util::formatString(14, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [10] Logout"              << Util::formatString(24, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
    }

public:
    static void showMainScreen()
    {
        _showMainMenuOptions();
        _performMainMenuOption(_readMainMenuOption());
    }
};