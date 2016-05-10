#pragma once
#include "Clients.h"
#include "Product.h"
#include "Products.h"
#include "Transactions.h"

#include <vector>

using namespace std;

class Advertising
{
private:
	Clients * clients;
	Products * products;
	Transactions * transactions;
public:
	Advertising(Clients * clients, Products * products, Transactions * transactions);
	vector<unsigned int> getAdvertising(unsigned int clientId);
};

