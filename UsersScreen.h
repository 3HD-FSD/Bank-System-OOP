#pragma once
#include "Screen.h"
#include "InputValidation.h"
#include "UsersListScreen.h"
#include "AddUserScreen.h"
#include "DeleteUserScreen.h"
#include "UpdateUserScreen.h"
#include "FindUserScreen.h"

class UsersScreen : protected Screen
{
private:
    enum enUsersMenuOption
    {
        ShowUsers = 1,
        AddUser = 2,
        DeleteUser = 3,
        UpdateUser = 4,
        FindUser = 5,
        Exit = 6
    };

    static void _goBackToUsersMenu()
    {
        cout << "\n" << Util::tabs(5) << "Press [Enter] key to go back to users menu...";
        system("pause>0");
        showUsersScreen();
    }

    static enUsersMenuOption _readUsersMenuOption()
    {
        cout << Util::tabs(5) << "Choose any service [1 -> 6] : ";
        enUsersMenuOption choice = enUsersMenuOption(InputValidation::readIntNumberBetween(1, 6, Util::tabs(5) + "Invalid input, choose any service [1 -> 6] : "));
        return choice;
    }

    static void _showAllUsersScreen()
    {
        UsersListScreen::showUsersListScreen();
    }

    static void _showAddUserScreen()
    {
        AddUserScreen::showAddUserScreen();
    }

    static void _showDeleteUserScreen()
    {
        DeleteUserScreen::showDeleteUserScreen();
    }

    static void _showUpdateUserScreen()
    {
        UpdateUserScreen::showUpdateUserScreen();
    }

    static void _showFindUserScreen()
    {
        FindUserScreen::showFindUserScreen();
    }

    static void _showScreen(void(*screen)())
    {
        system("cls");
        screen();
        _goBackToUsersMenu();
    }

    static void _performUsersMenuOption(enUsersMenuOption choice)
    {
        switch (choice)
        {
        case enUsersMenuOption::ShowUsers:
            _showScreen(_showAllUsersScreen);
            break;
        case enUsersMenuOption::AddUser:
            _showScreen(_showAddUserScreen);
            break;
        case enUsersMenuOption::DeleteUser:
            _showScreen(_showDeleteUserScreen);
            break;
        case enUsersMenuOption::UpdateUser:
            _showScreen(_showUpdateUserScreen);
            break;
        case enUsersMenuOption::FindUser:
            _showScreen(_showFindUserScreen);
            break;
        case enUsersMenuOption::Exit:
            break;
        default:
            cout << "Error!" << endl;
            break;
        }
    }

    static void _showMainMenuOptions()
    {
        system("cls");
        _showScreenHeader("Users Menu Screen");

        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << Util::formatString(38, "Users Management", Util::enAlign::CENTER) << "|" << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << "    [1] Show Users List" << Util::formatString(16, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [2] Add New User" << Util::formatString(19, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [3] Delete User" << Util::formatString(20, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [4] Update User Data" << Util::formatString(15, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [5] Find User" << Util::formatString(22, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [6] Exit" << Util::formatString(27, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
    }

public:
    static void showUsersScreen()
    {
        _showMainMenuOptions();
        _performUsersMenuOption(_readUsersMenuOption());
    }
};