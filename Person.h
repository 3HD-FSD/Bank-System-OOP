#pragma once

#include <iostream>
#include <string>

using namespace std;

class Person
{
private:
	string _firstName;
	string _lastName;
	string _phone;
	string _email;

public:
	Person(string firstName, string lastName, string phone, string email)
	{
		_firstName = firstName;
		_lastName = lastName;
		_phone = phone;
		_email = email;
	}

	void setFirstName(string firstName)
	{
		_firstName = firstName;
	}

	string getFirstName()
	{
		return _firstName;
	}

	__declspec(property(put = setFirstName, get = getFirstName)) string firstName;

	void setLastName(string lastName)
	{
		_lastName = lastName;
	}

	string getLastName()
	{
		return _lastName;
	}

	__declspec(property(put = setLastName, get = getLastName)) string lastName;

	string getFullName()
	{
		return _firstName + " " + _lastName;
	}

	void setPhone(string phone)
	{
		_phone = phone;
	}

	string getPhone()
	{
		return _phone;
	}

	__declspec(property(put = setPhone, get = getPhone)) string phone;

	void setEmail(string email)
	{
		_email = email;
	}

	string getEmail()
	{
		return _email;
	}

	__declspec(property(put = setEmail, get = getEmail)) string email;
};

