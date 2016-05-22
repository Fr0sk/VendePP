/*
* Grupo: T7G03
*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

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
	vector<vector<bool>> computeBoolMatrix();
	vector<unsigned int> computeProductsCount();
	unsigned int getNumberOfProductsBought(vector<bool> productList);
	vector<unsigned int> calculateHistogram(vector<unsigned int> clientIndexes);
public:
	Advertising(Clients * clients, Products * products, Transactions * transactions);
	Product getAdvertising(unsigned int clientId);
	Product getAdvertising(vector<Client> ClientList);
};

