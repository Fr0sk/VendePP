#pragma once
#include "Date.h"

#include <string>

using namespace std;

class Client
{
private:
	unsigned int id;
	string name;
	Date joinDate;
	double amountPaid;
public:
	Client(unsigned int id, string name, Date joinDate, double amountPaid);
	unsigned int getId() const;
	string getName() const;
	Date getJoinDate() const;
	void setName(string value);
	double getAmountPaid() const;
	void addPayment(double value);
};

