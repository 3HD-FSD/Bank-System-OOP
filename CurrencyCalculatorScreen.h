#pragma once
#include "Screen.h"

class CurrencyCalculatorScreen : protected Screen
{
private:
	static string _readCurrencyCode()
	{
		string currencyCode;
		currencyCode = InputValidation::readString();
		return currencyCode;
	}

	static void _printConvertedCurrencyInfo(Currency& currency)
	{
		cout << "\nConvert From\n";
		cout << "------------------------------" << endl;
		cout << "Country      : " << currency.getCountry() << endl;
		cout << "Code         : " << currency.getCurrencyCode() << endl;
		cout << "Name         : " << currency.getCurrencyName() << endl;
		cout << "Rate (1$)    : " << to_string(currency.getRate()) << endl;
		cout << "------------------------------" << endl;
	}

public:
	static void showCurrencyCalculatorScreen()
	{
		char choice;
		do
		{
			system("cls");
			string title = "Currency Calculator Screen";

			_showScreenHeader(title);
			cout << "\nEnter first currency code : ";
			string currencyCode1 = _readCurrencyCode();
			Currency currency1 = Currency::findByCurrencyCode(currencyCode1);

			while (currency1.isEmpty())
			{
				cout << currencyCode1 << " not found, enter a nother currency code : ";
				currencyCode1 = _readCurrencyCode();
				currency1 = Currency::findByCurrencyCode(currencyCode1);
			}

			cout << "\nEnter second currency code : ";
			string currencyCode2 = _readCurrencyCode();
			Currency currency2 = Currency::findByCurrencyCode(currencyCode2);

			while (currency2.isEmpty())
			{
				cout << currencyCode2 << " not found, enter a nother currency code : ";
				currencyCode2 = _readCurrencyCode();
				currency2 = Currency::findByCurrencyCode(currencyCode2);
			}

			cout << "\nEnter amount to exchange : ";
			float amount = InputValidation::readPositiveFloatNumber();

			_printConvertedCurrencyInfo(currency1);

			cout << "\n" << amount << " " << currency1.getCurrencyCode() << " = " << currency1.convertToOtherCurrency(currency2, amount) << " " << currency2.getCurrencyCode() << endl;

			cout << "\nDo you want ot perform a nother calculation ? Y / N ? ";
			choice = InputValidation::readYesOrNo();
		} while (toupper(choice) == 'Y');
	}
};