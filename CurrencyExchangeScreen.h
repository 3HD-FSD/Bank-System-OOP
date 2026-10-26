#pragma once
#include "Screen.h"
#include "CurrenciesListScreen.h"
#include "FindCurrencyScreen.h"
#include "UpdateRateScreen.h"
#include "CurrencyCalculatorScreen.h"

class CurrencyExchangeScreen : protected Screen
{
private:
    enum enCurrencyExchangeMenuOption
    {
        ShowCurrenciesList = 1,
        FindCurrency = 2,
        UpdateRate = 3,
        CurrencyCalculator = 4,
        Exit = 5,
    };

    static void _goBackToCurrencyExchangeMenu()
    {
        cout << "\n" << Util::tabs(5) << "Press [Enter] key to go back to currency exchange menu...";
        system("pause>0");
        showCurrencyExchangeScreen();
    }

    static enCurrencyExchangeMenuOption _readCurrencyExchangeMenuOption()
    {
        cout << Util::tabs(5) << "Choose any service [1 -> 5] : ";
        enCurrencyExchangeMenuOption choice = enCurrencyExchangeMenuOption(InputValidation::readIntNumberBetween(1, 5, Util::tabs(5) + "Invalid input, choose any service [1 -> 5] : "));
        return choice;
    }

    static void _showCurrenciesListScreen()
    {
        CurrenciesListScreen::showCurrenciesListScreen();
    }

    static void _showFindCurrencyScreen()
    {
        FindCurrencyScreen::showFindCurrencyScreen();
    }

    static void _showUpdateScreen()
    {
        UpdateRateScreen::showUpdateRateScreen();
    }

    static void _showCurrencyCalculatorScreen()
    {
        CurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    }

    static void _showScreen(void(*screen)())
    {
        system("cls");
        screen();
        _goBackToCurrencyExchangeMenu();
    }

    static void _performCurrencyExchangeMenuOption(enCurrencyExchangeMenuOption choice)
    {
        switch (choice)
        {
        case enCurrencyExchangeMenuOption::ShowCurrenciesList:
            _showScreen(_showCurrenciesListScreen);
            break;
        case enCurrencyExchangeMenuOption::FindCurrency:
            _showScreen(_showFindCurrencyScreen);
            break;
        case enCurrencyExchangeMenuOption::UpdateRate:
            _showScreen(_showUpdateScreen);
            break;
        case enCurrencyExchangeMenuOption::CurrencyCalculator:
            _showScreen(_showCurrencyCalculatorScreen);
            break;
        case enCurrencyExchangeMenuOption::Exit:
            break;
        default:
            cout << "Error!" << endl;
            break;
        }
    }

    static void _showCurrencyExchangeMenuOptions()
    {
        system("cls");
        _showScreenHeader("Currency Exchange Menu Screen");

        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << Util::formatString(38, "Currency Exchange Management", Util::enAlign::CENTER) << "|" << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
        cout << Util::tabs(5) << "|" << "    [1] Currencies List" << Util::formatString(16, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [2] Find Currency" << Util::formatString(18, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [3] Update Rate" << Util::formatString(20, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [4] Currency Calculator" << Util::formatString(12, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << "|" << "    [5] Exit" << Util::formatString(27, "|", Util::enAlign::RIGHT) << endl;
        cout << Util::tabs(5) << Util::characters('-', 40) << endl;
    }

public:
    static void showCurrencyExchangeScreen()
    {
        _showCurrencyExchangeMenuOptions();
        _performCurrencyExchangeMenuOption(_readCurrencyExchangeMenuOption());
    }

};