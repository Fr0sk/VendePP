#include "Date.h"
#include <ctime>
#include <sstream>


Date Date::createDate(unsigned int day, unsigned int month, unsigned int year)
{
	// Validates date
	if (month < 1 || month > 12)
		return Date();
	if (day < 0 || day > 31)
		return Date();
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return Date();
	if (month == 2)
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && day > 29 || day > 28)
			return Date();
		
	return Date(day, month, year);
}

unsigned int Date::getDay() const
{
	return day;
}

unsigned int Date::getMonth() const
{
	return month;
}

unsigned int Date::getYear() const
{
	return year;
}

string Date::toString() const
{
	stringstream ss;
	ss << day << "/" << month << "/" << year;
	return ss.str();
}

bool Date::operator<(const Date & right) const
{
	if (this->year < right.year)
		return true;
	else if (this->year > right.year)
		return false;
	else {
		if (this->month < right.month)
			return true;
		else if (this->month > right.month)
			return false;
		else
			return this->day < right.day;
	}
}

bool Date::operator==(const Date & right) const
{
	return (this->day == right.day && this->month == right.month && this->year == right.year);
}

Date::Date()
{
	time_t t = time(0); // time now
	struct tm * now = localtime(&t);
	day = now->tm_mday;
	month = now->tm_mon;
	year = now->tm_year + 1900;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) :
	day(day),
	month(month),
	year(year)
{
	// Empty block
}

Date::Date(string date)
{
	day = (unsigned int)std::stoi(date.substr(0, date.find("/")));
	date = date.substr(date.find("/") + 1);
	month = (unsigned int)std::stoi(date.substr(0, date.find("/")));
	date = date.substr(date.find("/") + 1);
	year = (unsigned int)std::stoi(date);
}
