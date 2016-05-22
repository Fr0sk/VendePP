/*
* Grupo: T7G03*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#pragma once
#include "Product.h"
#include "Date.h"

#include <vector>
#include <string>

using namespace std;

class Transaction
{
	unsigned int clientId;
	Date date;
	vector<Product> products;
	
public:
	Transaction(unsigned int clientId, Date date, vector<Product> products);
	unsigned int getClientId() const;
	Date getDate() const;
	vector<Product> getProducts() const;
};
