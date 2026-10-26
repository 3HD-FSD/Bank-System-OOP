#pragma once
#include "Screen.h"
#include "Currency.h"
#include "InputValidation.h"

class FindCurrencyScreen : protected Screen
{
private:
	enum enFindType { Code = 1, Country = 2 };

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

	static enFindType _readFindType()
	{
		short findType;
		cout << "Find by: [1] Code or [2] Country ? ";
		findType = InputValidation::readIntNumberBetween(1, 2);
		return enFindType(findType);
	}

	static string _readCurrencyCode()
	{
		string currencyCode;
		cout << "\nEnter currency code : ";
		currencyCode = InputValidation::readString();
		return currencyCode;
	}

	static string _readCurrencyCountry()
	{
		string currencyCountry;
		cout << "\nEnter currency country : ";
		currencyCountry = InputValidation::readString();
		return currencyCountry;
	}

	static void _findResult(Currency currency)
	{
		if (!currency.isEmpty())
		{
			cout << "\nCurrency found!" << endl;
			_printCurrencyInfo(currency);
		}
		else
		{
			cout << "\nCurrency not found!" << endl;
		}
	}
public:



	static void showFindCurrencyScreen()
	{
		string title = "Find Currency Screen";

		_showScreenHeader(title);

		enFindType findType = _readFindType();

		if (findType == enFindType::Code)
		{
			string currencyCode = _readCurrencyCode();
			Currency currency = Currency::findByCurrencyCode(currencyCode);
			_findResult(currency);
		}
		else
		{
			string currencyCountry = _readCurrencyCountry();
			Currency currency = Currency::findByCountry(currencyCountry);
			_findResult(currency);
		}
	}
};