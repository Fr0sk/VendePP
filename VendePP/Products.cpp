#include "Products.h"

#include <iostream>

void Products::setupDatabase(string path)
{
	database.setPath(path);
	database.setParams(2);
}

void Products::load()
{
	vector<string> productsList;
	database.read(productsList);

	vector<Product> tmpProducts;

	for (vector<string>::iterator it = productsList.begin() + 1; it != productsList.end(); it++)
	{
		string name = (*it++);
		double price = stod(*it);
		Product p(name, price);
		tmpProducts.push_back(p);
	}
	products.clear();
	products = tmpProducts;
}

void Products::save()
{
	vector<string> values;
	values.push_back(to_string(size()));

	for (vector<Product>::const_iterator it = products.begin(); it != products.end(); it++)
	{
		values.push_back((*it).getName());
		values.push_back(to_string((*it).getPrice()));
	}
	database.write(values);
}

Products::Products(string databasePath)
{
	setupDatabase(databasePath);
	load();
}

unsigned int Products::size()
{
	return products.size();
}

bool Products::printProduct(unsigned int index)
{
	if(index >= products.size())
		cout << "There is no product with ID: " << index << endl;
	else {
		Product product = products.at(index);
		cout << "Product: " << endl;
		cout << "\t   Name: " << product.getName() << endl;
		cout << "\t   Price: " << product.getPrice() << endl;
		return true;
	}
	return false;
}

void Products::dump()
{
	for (unsigned int index = 0; index < size(); index++)
	{
		printProduct(index);
		cout << endl;
	}
		
}

void Products::addProduct(string name, double price)
{
	Product p(name, price);
	products.push_back(p);
	save();
}

void Products::editProduct(unsigned int index, string name, double price)
{
	products.at(index).setName(name);
	products.at(index).setPrice(price);
	save();
}

Product Products::getProduct(string name)
{
	for (vector<Product>::iterator it = products.begin(); it != products.end(); it++)
		if ((*it).getName() == name)
			return (*it);
	return Product("", 0);
}