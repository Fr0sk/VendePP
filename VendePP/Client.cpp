#include "Client.h"
#include <string>

using namespace std;

Client::Client(unsigned int id, string name, Date joinDate, double amountPaid) :
	id(id),
	name(name),
	joinDate(joinDate),
	amountPaid(amountPaid)
{
	// Empty block
}

unsigned int Client::getId() const
{
	return id;
}

string Client::getName() const
{
	return name;
}

Date Client::getJoinDate() const
{
	return joinDate;
}

void Client::setName(string value)
{
	if (name != value)
		name = value;
}

double Client::getAmountPaid() const
{
	return amountPaid;
}

void Client::addPayment(double value)
{
	if (value > 0)
		amountPaid += value;
}