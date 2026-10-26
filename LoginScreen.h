#pragma once
#include "Screen.h"
#include "User.h"
#include "Global.h"
#include "MainScreen.h"

class LoginScreen : protected Screen
{
private:
    static void _login()
    {
        bool loginFaild = false;
        string userName, password;
        short trials = 3;

        do
        {
            if (loginFaild)
            {
                trials--;
                cout << "\n" << Util::tabs(5) << "Incorrect username/password, you have " << trials << " trial(s)!\n" << endl;
            }

            if (trials == 0)
            {
                cout << "\n" << Util::tabs(5) << "The system was locked after 3 faild trials!" << endl;
                exit(0);
            }

            cout << Util::tabs(5) << "Enter username : ";
            cin >> userName;
            cout << Util::tabs(5) << "Enter password : ";
            cin >> password;

            currentUser = User::find(userName, password);

            loginFaild = currentUser.isEmpty();
        } while (loginFaild);

        currentUser.registerLogin();
        MainScreen::showMainScreen();
    }
public:
    static void showLoginScreen()
    {
        string title = "Login Screen";

        _showScreenHeader(title);

        _login();
    }
};

