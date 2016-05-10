#pragma once
#include <string>

using namespace std;

class Date
{
	unsigned int day;
	unsigned int month;
	unsigned int year;

	Date(unsigned int day, unsigned int month, unsigned int year);
	Date();
public:
	Date(string date);
	static Date createDate(unsigned int day = 0, unsigned int month = 0, unsigned int year = 0);
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	string toString() const;
	bool operator< (const Date& right) const;
	bool operator==(const Date& right) const;
};

