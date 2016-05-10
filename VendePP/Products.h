#pragma once
#include "Product.h"
#include "Database.h"

#include <string>
#include <vector>

using namespace std;

class Products
{
private:
	vector<Product> products;
	Database database;

	void setupDatabase(string path);
	void load();
	void save();

public:
	Products(string databasePath);
	unsigned int size();
	bool printProduct(unsigned int productId);
	void dump();
	void addProduct(string name, double price);
	void editProduct(unsigned int index, string name, double price);
	Product getProduct(string name);
};

