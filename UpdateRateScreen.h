#pragma once
#include "Screen.h"
class UpdateRateScreen : protected Screen
{
private:
	static string _readCurrencyCode()
	{
		string currencyCode;
		cout << "\nEnter currency code : ";
		currencyCode = InputValidation::readString();
		return currencyCode;
	}

	static void _updateCurrencyRate(Currency& currency)
	{
		cout << "\nUpdate Currency Rate:" << endl;
		cout << "------------------------------" << endl;
		cout << "Enter new rate : ";
		float newRate = InputValidation::readPositiveFloatNumber();
		currency.updateRate(newRate);
		cout << "\nCurrency rate updated successfully!" << endl;
	}

	static void _printCurrencyInfo(Currency& currency)
	{
		cout << "\nCurrency Data\n";
		cout << "------------------------------" << endl;
		cout << "Country      : " << currency.getCountry() << endl;
		cout << "Code         : " << currency.getCurrencyCode() << endl;
		cout << "Name         : " << currency.getCurrencyName() << endl;
		cout << "Rate (1$)    : " << to_string(currency.getRate()) << endl;
		cout << "------------------------------" << endl;
	}

public:
	static void showUpdateRateScreen()
	{
		string title = "Update Rate Screen";

		_showScreenHeader(title);

		string currencyCode = _readCurrencyCode();

		Currency currency = Currency::findByCurrencyCode(currencyCode);

		if (!currency.isEmpty())
		{
			_printCurrencyInfo(currency);
			cout << "\nAre you sure you want to update the rate of this currency ? Y / N ? ";
			char choice = InputValidation::readYesOrNo();
			if (toupper(choice) == 'Y')
			{
				_updateCurrencyRate(currency);
				_printCurrencyInfo(currency);
			}
			else
			{
				cout << "\nOperation was cancelled!" << endl;
			}
		}
		else
		{
			cout << "\nCurrency not found!" << endl;
		}
	}
};