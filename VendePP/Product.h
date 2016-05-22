/*
* Grupo: T7G03*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#pragma once
#include <string>

using namespace std;

class Product
{
private:
	string name;
	double price;
public:
	Product(string name, double price);
	string getName() const;
	void setName(string value);
	double getPrice() const;
	void setPrice(double value);
};

