#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include "String.h"
#include <iomanip>

using namespace std;

class Date
{
private:
	short _day, _month, _year;
public:
	Date()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_day = now->tm_mday;
		_month = now->tm_mon + 1;
		_year = now->tm_year + 1900;
	}

	Date(string date)
	{
		vector <string> vDate = String::split(date, "/");
		_day = stoi(vDate[0]);
		_month = stoi(vDate[1]);
		_year = stoi(vDate[2]);
	}

	Date(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	Date(short dateOrderInYear, short year)
	{
		Date date = getDateFromDayOrderInYear(dateOrderInYear, year);
		_day = date.day;
		_month = date.month;
		_year = date.year;
	}

	void setDay(short day)
	{
		_day = day;
	}

	short getDay()
	{
		return _day;
	}

	void setMonth(short month)
	{
		_month = month;
	}

	short getMonth()
	{
		return _month;
	}

	void setYear(short year)
	{
		_year = year;
	}

	short getYear()
	{
		return _year;
	}

	__declspec(property(put = setDay, get = getDay)) short day;
	__declspec(property(put = setMonth, get = getMonth)) short month;
	__declspec(property(put = setYear, get = getYear)) short year;

	static string dateToString(Date date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}

	string dateToString()
	{
		return dateToString(*this);
	}

	static Date getSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short day, month, year;

		day = now->tm_mday;
		month = now->tm_mon + 1;
		year = now->tm_year + 1900;

		return Date(day, month, year);
	}

	static string timeToString(tm* now)
	{
		return to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
	}

	static tm* getSystemTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		return now;
	}

	static bool isLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool isLeap()
	{
		return isLeap(_year);
	}

	static short numberOfDaysInThisYear(short year)
	{
		return (isLeap(year) ? 366 : 365);
	}

	short numberOfDaysInThisYear()
	{
		return numberOfDaysInThisYear(_year);
	}

	static short numberOfHoursInThisYear(short year)
	{
		return numberOfDaysInThisYear(year) * 24;
	}

	short numberOfHoursInThisYear()
	{
		return numberOfHoursInThisYear(_year);
	}

	static short numberOfMinutesInThisYear(short year)
	{
		return numberOfHoursInThisYear(year) * 60;
	}

	short numberOfMinutesInThisYear()
	{
		return numberOfMinutesInThisYear(_year);
	}

	static short numberOfSecondsInThisYear(short year)
	{
		return numberOfMinutesInThisYear(year) * 60;
	}

	short numberOfSecondsInThisYear()
	{
		return numberOfSecondsInThisYear(_year);
	}

	static short numberOfDaysInThisMonth(short month, short year)
	{
		short days[12] = { 31, (isLeap(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return days[month - 1];
	}

	short numberOfDaysInThisMonth()
	{
		return numberOfDaysInThisMonth(_month, _year);
	}

	static short numberOfHoursInThisMonth(short month, short year)
	{
		return numberOfDaysInThisMonth(month, year) * 24;
	}

	short numberOfHoursInThisMonth()
	{
		return numberOfHoursInThisMonth(_month, _year);
	}

	static short numberOfMinutesInThisMonth(short month, short year)
	{
		return numberOfHoursInThisMonth(month, year) * 60;
	}

	short numberOfMinutesInThisMonth()
	{
		return numberOfMinutesInThisMonth(_month, _year);
	}

	static short numberOfSecondsInThisMonth(short month, short year)
	{
		return numberOfMinutesInThisMonth(month, year) * 60;
	}

	short numberOfSecondsInThisMonth()
	{
		return numberOfSecondsInThisMonth(_month, _year);
	}

	static short dayOfWeekOrder(short day, short month, short year)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(_day, _month, _year);
	}

	static string dayName(short dayOfWeekOrder)
	{
		string daysNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return daysNames[dayOfWeekOrder];
	}

	static string dayName(short day, short month, short year)
	{
		string daysNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return daysNames[dayOfWeekOrder(day, month, year)];
	}

	string dayName()
	{
		return dayName(_day, _month, _year);
	}

	static string monthName(short month)
	{
		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[month - 1];
	}

	string monthName()
	{
		return monthName(_month);
	}

	static void printCalendar(short month, short year)
	{
		short numberOfDays = numberOfDaysInThisMonth(month, year);
		short dayOrder = dayOfWeekOrder(1, month, year);

		cout << "-----------------" << monthName(month) << "-----------------" << endl;
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat  " << endl;
		for (int i = 0; i < dayOrder; i++)
		{
			cout << "     ";
		}
		for (int i = 1, j = dayOrder; i <= numberOfDays; i++)
		{
			cout << setw(5) << i;
			j++;
			if (j == 7)
			{
				j = 0;
				cout << "\n";
			}
		}
		cout << "\n-------------------------------------" << endl;
	}

	void printCalendar()
	{
		printCalendar(_month, _year);
	}

	static void printYearCalendar(short year)
	{
		cout << "-------------------------------------" << endl;
		cout << "               " << setw(7) << year << "               " << endl;
		cout << "-------------------------------------" << endl;
		for (int i = 1; i <= 12; i++)
		{
			printCalendar(i, year);
		}
	}

	void printYearCalendar()
	{
		printYearCalendar(_year);
	}

	static bool isValid(Date date)
	{
		if (date.day < 1 || date.day > numberOfDaysInThisMonth(date.month, date.year)) {
			return false;
		}
		if (date.month < 1 || date.month > 12)
		{
			return false;
		}
		if (date.year < 1)
		{
			return false;
		}
		return true;
	}

	bool isValid()
	{
		return isValid(*this);
	}

	static short numberOfDaysFromTheBeginningOfYear(short day, short month, short year)
	{
		short totalDays = 0;
		for (int i = 1; i < month; i++)
		{
			totalDays += numberOfDaysInThisMonth(month, year);
		}
		totalDays += day;
		return totalDays;
	}

	short numberOfDaysFromTheBeginningOfYear()
	{
		return numberOfDaysFromTheBeginningOfYear(_day, _month, _year);
	}

	static Date getDateFromDayOrderInYear(short dateOrderInYear, short year)
	{
		short months = 1;
		short days = 0;
		short numberOfDays;
		for (int i = 1; i <= 12; i++)
		{
			numberOfDays = numberOfDaysInThisMonth(i, year);
			if (dateOrderInYear > numberOfDays)
			{
				months++;
				dateOrderInYear -= numberOfDays;
			}
			else
			{
				days = dateOrderInYear;
				break;
			}
		}
		return Date(days, months, year);
	}

	static Date addDays(Date date, int days)
	{
		short totalDays = numberOfDaysFromTheBeginningOfYear(date.day, date.month, date.year) + days;
		short monthDays;
		date.month = 1;
		while (true)
		{
			monthDays = numberOfDaysInThisMonth(date.month, date.year);
			if (totalDays > monthDays)
			{
				date.month++;
				totalDays -= monthDays;

				if (date.month == 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day = totalDays;
				break;
			}
		}
		return date;
	}

	void addDays(int days)
	{
		*this = addDays(*this, days);
	}

	static bool isLastMonthInYear(short month)
	{
		return (month == 12);
	}

	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_month);
	}

	static bool isLastDayInMonth(Date date)
	{
		return (date.day == numberOfDaysInThisMonth(date.month, date.year));
	}

	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static Date addOneDay(Date date) {
		if (isLastDayInMonth(date))
		{
			if (isLastMonthInYear(date.month))
			{
				date.day = 1;
				date.month = 1;
				date.year++;
			}
			else
			{
				date.day = 1;
				date.month++;
			}
		}
		else
		{
			date.day++;
		}
		return date;
	}

	static void swap(Date& date1, Date& date2)
	{
		Date temp = date1;
		date1 = date2;
		date2 = temp;
	}

	static bool isDate1BeforeDate2(Date date1, Date date2)
	{
		return (date1.year < date2.year ? true : (date1.year == date2.year ? (date1.month < date2.month ? true : (date1.month == date2.month ? (date1.day < date2.day) : false)) : false));
	}

	bool before(Date date)
	{
		return isDate1BeforeDate2(*this, date);
	}

	static bool isDate1EqualDate2(Date date1, Date date2)
	{
		return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
	}

	bool equal(Date date)
	{
		return isDate1EqualDate2(*this, date);
	}

	static bool isDate1AfterDate2(Date date1, Date date2)
	{
		return !isDate1EqualDate2(date1, date2) && !isDate1BeforeDate2(date1, date2);
	}

	bool after(Date date)
	{
		return isDate1AfterDate2(*this, date);
	}

	static int getDifferenceInDays(Date date1, Date date2, bool includeEndDay = false)
	{
		int days = 0;
		short swapFlag = 1;

		if (isDate1BeforeDate2(date1, date2))
		{
			swap(date1, date2);
			swapFlag = -1;
		}

		while (isDate1BeforeDate2(date1, date2))
		{
			days++;
			date1 = addOneDay(date1);
		}

		return includeEndDay ? ++days * swapFlag : days * swapFlag;
	}

	int getDifferenceInDays(Date date, bool includeEndDay = false)
	{
		return getDifferenceInDays(*this, date, includeEndDay);
	}

	static short calculateAgeInDays(Date birthDate)
	{
		return getDifferenceInDays(birthDate, getSystemDate(), true);
	}

	static Date increaseDateByOneWeek(Date& date)
	{
		for (int i = 1; i <= 7; i++)
		{
			date = addOneDay(date);
		}

		return date;
	}

	void increaseDateByOneWeek()
	{
		increaseDateByOneWeek(*this);
	}

	Date increaseDateByXWeeks(short weeks, Date& date)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = increaseDateByOneWeek(date);
		}
		return date;
	}

	void increaseDateByXWeeks(short weeks)
	{
		increaseDateByXWeeks(weeks, *this);
	}

	Date increaseDateByOneMonth(Date& date)
	{
		if (date.month == 12)
		{
			date.month = 1;
			date.year++;
		}
		else
		{
			date.month++;
		}

		short numberOfDays = numberOfDaysInThisMonth(date.month, date.year);

		if (date.day > numberOfDays)
		{
			date.day = numberOfDays;
		}

		return date;
	}

	void increaseDateByOneMonth()
	{
		increaseDateByOneMonth(*this);
	}

	Date increaseDateByXDays(short days, Date& date)
	{
		for (short i = 1; i <= days; i++)
		{
			date = addOneDay(date);
		}
		return date;
	}

	void increaseDateByXDays(short days)
	{
		increaseDateByXDays(days, *this);
	}

	Date increaseDateByXMonths(short months, Date& date)
	{
		for (short i = 1; i <= months; i++)
		{
			date = increaseDateByOneMonth(date);
		}
		return date;
	}

	void increaseDateByXMonths(short months)
	{
		increaseDateByXMonths(months, *this);
	}

	static Date increaseDateByOneYear(Date& date)
	{
		date.year++;
		return date;
	}

	void increaseDateByOneYear()
	{
		increaseDateByOneYear(*this);
	}

	Date increaseDateByXYears(short years, Date& date)
	{
		date.year += years;
		return date;

	}

	void increaseDateByXYears(short years)
	{
		increaseDateByXYears(years);
	}

	Date increaseDateByOneDecade(Date& date)
	{
		date.year += 10;
		return date;
	}

	void increaseDateByOneDecade()
	{
		increaseDateByOneDecade(*this);
	}

	Date increaseDateByXDecades(short decade, Date& date)
	{
		date.year += decade * 10;
		return date;
	}

	void increaseDateByXDecades(short decade)
	{
		increaseDateByXDecades(decade, *this);
	}

	Date increaseDateByOneCentury(Date& date)
	{
		date.year += 100;
		return date;
	}

	void increaseDateByOneCentury()
	{
		increaseDateByOneCentury(*this);
	}

	Date increaseDateByOneMillennium(Date& date)
	{
		date.year += 1000;
		return date;
	}

	Date increaseDateByOneMillennium()
	{
		increaseDateByOneMillennium(*this);
	}

	static Date decreaseDateByOneDay(Date date)
	{
		if (date.day == 1)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.day = 31;
				date.year--;
			}
			else
			{
				date.month--;
				date.day = numberOfDaysInThisMonth(date.month, date.year);
			}
		}
		else
		{
			date.day--;
		}

		return date;
	}

	void decreaseDateByOneDay()
	{
		decreaseDateByOneDay(*this);
	}

	static Date decreaseDateByOneWeek(Date& date)
	{
		for (int i = 1; i <= 7; i++)
		{
			date = decreaseDateByOneDay(date);
		}

		return date;
	}

	void decreaseDateByOneWeek()
	{
		decreaseDateByOneWeek(*this);
	}

	static Date decreaseDateByXWeeks(short weeks, Date& date)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = decreaseDateByOneWeek(date);
		}
		return date;
	}

	void decreaseDateByXWeeks(short weeks)
	{
		decreaseDateByXWeeks(weeks, *this);
	}

	static Date decreaseDateByOneMonth(Date& date)
	{
		if (date.month == 1)
		{
			date.month = 12;
			date.year--;
		}
		else
		{
			date.month--;
		}
		short numberOfDays = numberOfDaysInThisMonth(date.month, date.year);
		if (date.day > numberOfDays)
		{
			date.day = numberOfDays;
		}
		return date;
	}

	void decreaseDateByOneMonth()
	{
		decreaseDateByOneMonth(*this);
	}

	static Date decreaseDateByXDays(short days, Date& date)
	{
		for (short i = 1; i <= days; i++)
		{
			date = decreaseDateByOneDay(date);
		}
		return date;
	}

	void decreaseDateByXDays(short days)
	{
		decreaseDateByXDays(days, *this);
	}

	static Date decreaseDateByXMonths(short months, Date& date)
	{
		for (short i = 1; i <= months; i++)
		{
			date = decreaseDateByOneMonth(date);
		}
		return date;
	}

	void decreaseDateByXMonths(short months)
	{
		decreaseDateByXMonths(months, *this);
	}

	static Date decreaseDateByOneYear(Date& date)
	{
		date.year--;
		return date;
	}

	void decreaseDateByOneYear()
	{
		decreaseDateByOneYear(*this);
	}

	static Date decreaseDateByXYears(short years, Date& date)
	{
		date.year -= years;
		return date;
	}

	void decreaseDateByXYears(short years)
	{
		decreaseDateByXYears(years, *this);
	}

	static Date decreaseDateByOneDecade(Date& date)
	{
		date.year -= 10;
		return date;
	}

	void decreaseDateByOneDecade()
	{
		decreaseDateByOneDecade(*this);
	}

	static Date decreaseDateByXDecades(short decades, Date& date)
	{
		date.year -= decades * 10;
		return date;
	}

	void decreaseDateByXDecades(short decades)
	{
		decreaseDateByXDecades(decades, *this);
	}

	static Date decreaseDateByOneCentury(Date& date)
	{
		date.year -= 100;
		return date;
	}

	void decreaseDateByOneCentury()
	{
		decreaseDateByOneCentury(*this);
	}

	static Date decreaseDateByOneMillennium(Date& date)
	{
		date.year -= 1000;
		return date;
	}

	void decreaseDateByOneMillennium()
	{
		decreaseDateByOneMillennium(*this);
	}


	static short isEndOfWeek(Date date)
	{
		return  dayOfWeekOrder(date.day, date.month, date.year) == 6;
	}

	short isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(Date date)
	{
		short dayOrder = dayOfWeekOrder(date.day, date.month, date.year);
		return  (dayOrder == 5 || dayOrder == 6);
	}

	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(Date date)
	{
		return !isWeekEnd(date);
	}

	bool isBusinessDay()
	{
		return  isBusinessDay(*this);
	}

	static short daysUntilTheEndOfWeek(Date date)
	{
		return 6 - dayOfWeekOrder(date.day, date.month, date.year);
	}

	short daysUntilTheEndOfWeek()
	{
		return  daysUntilTheEndOfWeek(*this);
	}

	static short daysUntilTheEndOfMonth(Date date1)
	{
		Date endOfMonthDate;
		endOfMonthDate.day = numberOfDaysInThisMonth(date1.month, date1.year);
		endOfMonthDate.month = date1.month;
		endOfMonthDate.year = date1.year;
		return getDifferenceInDays(date1, endOfMonthDate, true);
	}

	short daysUntilTheEndOfMonth()
	{
		return daysUntilTheEndOfMonth(*this);
	}

	static short daysUntilTheEndOfYear(Date date1)
	{
		Date endOfYearDate;
		endOfYearDate.day = 31;
		endOfYearDate.month = 12;
		endOfYearDate.year = date1.year;

		return getDifferenceInDays(date1, endOfYearDate, true);
	}

	short daysUntilTheEndOfYear()
	{
		return  daysUntilTheEndOfYear(*this);
	}

	static short calculateBusinessDays(Date dateFrom, Date dateTo)
	{
		short days = 0;
		while (isDate1BeforeDate2(dateFrom, dateTo))
		{
			if (isBusinessDay(dateFrom))
				days++;

			dateFrom = addOneDay(dateFrom);
		}
		return days;
	}

	static short calculateVacationDays(Date dateFrom, Date dateTo)
	{
		return calculateBusinessDays(dateFrom, dateTo);
	}

	static Date calculateVacationReturnDate(Date dateFrom, short vacationDays)
	{
		short weekEndCounter = 0;
		for (short i = 1; i <= vacationDays; i++)
		{
			if (isWeekEnd(dateFrom))
			{
				weekEndCounter++;
			}
			dateFrom = addOneDay(dateFrom);
		}
		for (short i = 1; i <= weekEndCounter; i++)
		{
			dateFrom = addOneDay(dateFrom);
		}
		return dateFrom;
	}

	bool isDateAfterDate2(Date date2)
	{
		return isDate1AfterDate2(*this, date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare compareDates(Date date1, Date date2)
	{
		if (isDate1BeforeDate2(date1, date2))
			return enDateCompare::Before;

		if (isDate1AfterDate2(date1, date2))
			return enDateCompare::After;

		return enDateCompare::Equal;
	}

	enDateCompare compareDates(Date date2)
	{
		return compareDates(*this, date2);
	}

	static string format(Date date, string formatStyle = "dd/mm/yyyy") {
		string formattedDate = "";

		formattedDate = String::smartReplace(formatStyle, "dd", to_string(date.day));
		formattedDate = String::smartReplace(formattedDate, "mm", to_string(date.month));
		formattedDate = String::smartReplace(formattedDate, "yyyy", to_string(date.year));

		return formattedDate;
	}

	string format(string formatStyle = "dd/mm/yyyy")
	{
		return format(*this, formatStyle);
	}

	void print()
	{
		cout << dateToString(*this) << endl;
	}

};