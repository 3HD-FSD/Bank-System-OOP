#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "String.h"

class Currency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _mode;

	string _country;
	string _currencyCode;
	string _currencyName;
	float _rate;

	static Currency _convertLineToCurrencyObject(string line, string seperator = ",")
	{
		vector<string> vCurrenciesData = String::split(line, seperator);

		string country = vCurrenciesData[0];
		string currencyCode = vCurrenciesData[1];
		string currencyName = vCurrenciesData[2];
		float rate = stof(vCurrenciesData[3]);

		return Currency(enMode::UpdateMode, country, currencyCode, currencyName, rate);
	}

	static vector<Currency> _loadCurrenciesDataFromFile()
	{
		vector<Currency> vCurrencies;

		fstream file;
		file.open("currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Currency currency = _convertLineToCurrencyObject(line, "#//#");
				vCurrencies.push_back(currency);
			}
			file.close();
		}
		return vCurrencies;
	}

	static string _convertCurrencyObjectToLine(Currency& currency, string seperator = ",")
	{
		string currencyData = "";

		currencyData += currency.getCountry() + seperator;
		currencyData += currency.getCurrencyCode() + seperator;
		currencyData += currency.getCurrencyName() + seperator;
		currencyData += to_string(currency.getRate());

		return currencyData;
	}

	static void _saveCurrenciesDataInFile(vector<Currency>& vCurrencies)
	{
		fstream file;
		file.open("currencies.txt", ios::out);

		if (file.is_open())
		{
			string line;
			for (Currency& currency : vCurrencies)
			{
				line = _convertCurrencyObjectToLine(currency, "#//#");
				file << line << endl;
			}
			file.close();
		}
	}

	static Currency _getEmptyCurrencyObject()
	{
		return Currency(enMode::EmptyMode, "", "", "", 0);
	}

	void _update()
	{
		vector<Currency> vCurrencies;

		vCurrencies = _loadCurrenciesDataFromFile();

		for (Currency& currency : vCurrencies)
		{
			if (getCurrencyCode() == currency.getCurrencyCode())
			{
				currency = *this;
				break;
			}
		}

		_saveCurrenciesDataInFile(vCurrencies);
	}

public:
	Currency(enMode mode, string country, string currencyCode, string currencyName, float rate)
	{
		_mode = mode;
		_country = country;
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_rate = rate;
	}

	string getCountry()
	{
		return _country;
	}

	string getCurrencyCode()
	{
		return _currencyCode;
	}

	string getCurrencyName()
	{
		return _currencyName;
	}

	float getRate()
	{
		return _rate;
	}



	void updateRate(float newRate)
	{
		_rate = newRate;
		_update();
	}



	bool isEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	static Currency findByCountry(string country)
	{
		country = String::upperAllLetters(country);

		fstream file;
		file.open("currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Currency currency = _convertLineToCurrencyObject(line, "#//#");
				if (country == String::upperAllLetters(currency.getCountry()))
				{
					file.close();
					return currency;
				}
			}
			file.close();
		}
		return _getEmptyCurrencyObject();
	}

	static Currency findByCurrencyCode(string currencyCode)
	{
		currencyCode = String::upperAllLetters(currencyCode);

		fstream file;
		file.open("currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Currency currency = _convertLineToCurrencyObject(line, "#//#");
				if (currencyCode == currency.getCurrencyCode())
				{
					file.close();
					return currency;
				}
			}
			file.close();
		}
		return _getEmptyCurrencyObject();
	}



	static bool isCurrencyExist(string currencyCode)
	{
		return !(findByCurrencyCode(currencyCode).isEmpty());
	}

	static vector<Currency> getCurrenciesList()
	{
		return _loadCurrenciesDataFromFile();
	}

	float convertToUSD(float amount)
	{
		return (float)(amount / getRate());
	}

	float convertToOtherCurrency(Currency currency2, float amount)
	{
		float amountInUSD = convertToUSD(amount);

		if (currency2.getCurrencyCode() == "USD")
		{
			return amountInUSD;
		}

		return (float)(amountInUSD * currency2.getRate());

	}
};