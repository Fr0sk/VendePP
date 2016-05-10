#include "Product.h"
#include <iostream>
#include <string>

using namespace std;

Product::Product(string name, double price) :
	name(name),
	price(price)
{
	// Empty block
}

string Product::getName() const
{
	return name;
}

void Product::setName(string value)
{
	if (name != value)
		name = value;
}

double Product::getPrice() const
{
	return price;
}

void Product::setPrice(double value)
{
	if (price != value)
		price = value;
}
