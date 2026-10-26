#pragma once

#include <iostream>
#include "Date.h"
#include "Util.h"

using namespace std;

class InputValidation
{
public:

	static int readPositiveIntNumber(string errorMessage = "Negative number, enter again : ")
	{
		int number;
		cin >> number;
		while (number <= 0)
		{
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static float readPositiveFloatNumber(string errorMessage = "Negative number, enter again : ")
	{
		float number;
		cin >> number;
		while (number <= 0)
		{
			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static bool isNumberBetween(int number, int from, int to)
	{
		if (from > to)
		{
			Util::swap(from, to);
		}
		return (number >= from && number <= to);
	}

	static bool isNumberBetween(float number, float from, float to)
	{
		if (from > to)
		{
			Util::swap(from, to);
		}
		return (number >= from && number <= to);
	}

	static bool isNumberBetween(double number, double from, double to)
	{
		if (from > to)
		{
			Util::swap(from, to);
		}
		return (number >= from && number <= to);
	}

	static bool isDateBetween(Date date, Date dateFrom, Date dateTo)
	{
		if (Date::isDate1AfterDate2(dateFrom, dateTo))
		{
			Date::swap(dateFrom, dateTo);
		}
		return !(date.before(dateFrom) || date.after(dateTo));
	}

	static int readIntNumber(string errorMessage = "Invalid number, enter again : ")
	{
		int number;
		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return number;
	}

	static int readIntNumberBetween(int from, int to, string errorMessage = "Invalid number, enter again : ")
	{
		int number = readIntNumber();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = readIntNumber();
		}
		return number;
	}

	static float readFloatNumber(string errorMessage = "Invalid number, enter again : ")
	{
		float number;
		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return number;
	}

	static float readFloatNumberBetween(float from, float to, string errorMessage = "Invalid number, enter again : ")
	{
		float number = readFloatNumber();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = readFloatNumber();
		}
		return number;
	}

	static double readDoubleNumber(string errorMessage = "Invalid number, enter again : ")
	{
		double number;
		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return number;
	}

	static double readDoubleNumberBetween(double from, double to, string errorMessage = "Invalid number, enter again : ")
	{
		double number = readDoubleNumber();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = readDoubleNumber();
		}
		return number;
	}

	static string readString()
	{
		string str;
		getline(cin >> ws, str);
		return str;
	}

	static char readChar()
	{
		char character;
		cin >> character;
		return character;
	}

	static char readYesOrNo(string errorMessage = "Invalid character, enter again : ")
	{
		char choice;
		cin >> choice;

		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			cout << errorMessage;
			cin >> choice;
		}
		
		return choice;
	}

	static bool isValidDate(Date date)
	{
		return date.isValid();
	}

	static string readEmail(string domainName = "@gmail.com")
	{
		string email = readString();
		while (!isValidEmail(email, domainName))
		{
			cout << "Invalid email, enter a valid email : ";
			email = readString();
		}
		return email;
	}

	static bool isValidEmail(string email, string domainName = "@gmail.com")
	{
		int pos;

		if ((pos = email.find(" ")) != std::string::npos)
			return false;
		else if ((pos = email.find("@")) != std::string::npos)
			email = email.substr(pos, domainName.length());
		
		return (email == domainName);
	}

};