#pragma once
#include "Screen.h"
#include "Currency.h"

class CurrenciesListScreen : protected Screen
{
private:
	static void _showCurrencyData(Currency& currency)
	{
		cout << "|" << Util::formatString(27, currency.getCountry(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(15, currency.getCurrencyCode(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(39, currency.getCurrencyName(), Util::enAlign::CENTER);
		cout << "|" << Util::formatString(16, to_string(currency.getRate()), Util::enAlign::CENTER) << "|" << endl;;
	}
public:
	static void showCurrenciesListScreen()
	{
		vector<Currency> vCurrencies = Currency::getCurrenciesList();

		string title = "Currencies List Screen";
		string subTitle = "(" + to_string(vCurrencies.size()) + ") Currency(s)";

		Screen::_showScreenHeader(title, subTitle);

		cout << Util::tabs(1) << Util::characters('-', 110) << endl;

		cout << Util::tabs(1) << "|" << "   #   ";
		cout << "|" << "          Country          ";
		cout << "|" << " Currency Code ";
		cout << "|" << "             Currency Name             ";
		cout << "|" << "    Rate/(1$)   " << "|" << endl;
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
		if (vCurrencies.size() == 0)
		{
			cout << Util::tabs(1) << "|" << Util::formatString(108, "No currencies found in the system.", Util::enAlign::CENTER) << "|" << endl;
		}
		else
		{
			int count = 0;
			for (Currency& currency : vCurrencies)
			{
				cout << Util::tabs(1) << "|" << Util::formatString(7, to_string(++count), Util::enAlign::CENTER);
				_showCurrencyData(currency);
			}
		}
		cout << Util::tabs(1) << Util::characters('-', 110) << endl;
	}
};