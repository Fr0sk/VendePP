/*
 * Grupo: T7G03
 * 
 * Filipe Coelho - 201500072
 * Luís Cruz - 201303248
 */

#include "Advertising.h"

#include <map>

// Calculates the boolean matrix
vector<vector<bool>> Advertising::computeBoolMatrix()
{
	vector<vector<bool>> matrix;

	// Creates a matrix with nClients rows and nProducts columns, initialized with false
	matrix.resize((*clients).size(), vector<bool>((*products).size(), false));

	for (int tIndex = 0; tIndex < (*transactions).size(); tIndex++)
	{
		Transaction t = (*transactions).getTransaction(tIndex);
		unsigned int tClientIndex = clients->getClientIndex(t.getClientId());
		vector<Product> tProducts = t.getProducts();

		for (vector<Product>::const_iterator tProduct = tProducts.begin(); tProduct != tProducts.end(); tProduct++)
		{
			unsigned int pIndex = (*products).getProductIndex(tProduct->getName());
			matrix.at(tClientIndex).at(pIndex) = true;
		}
	}
	return matrix;
}

// Counts how many times each product has been bought
vector<unsigned int> Advertising::computeProductsCount()
{
	vector<vector<bool>> matrix = computeBoolMatrix();
	vector<unsigned int> productCount;
	productCount.resize(products->size(), 0);

	for (int tIndex = 0; tIndex < (*transactions).size(); tIndex++)
	{
		Transaction t = (*transactions).getTransaction(tIndex);
		vector<Product> tProducts = t.getProducts();

		for (vector<Product>::const_iterator tProduct = tProducts.begin(); tProduct != tProducts.end(); tProduct++)
		{
			unsigned int pIndex = (*products).getProductIndex(tProduct->getName());
			productCount.at(pIndex) += 1;
		}
	}
	return productCount;
}

unsigned int Advertising::getNumberOfProductsBought(vector<bool> productList)
{
	unsigned int count = 0;
	for (vector<bool>::const_iterator bought = productList.begin(); bought != productList.end(); bought++)
		if (*bought)
			count += 1;
	return count;
}

vector<unsigned int> Advertising::calculateHistogram(vector<unsigned int> clientIndexes)
{
	vector<vector<bool>> matrix = computeBoolMatrix();
	vector<unsigned int> productHistogram;
	productHistogram.resize(products->size(), 0);

	for (vector<unsigned int>::const_iterator client = clientIndexes.begin(); client != clientIndexes.end(); client++)
	{
		vector<bool> productList = matrix.at(*client);
		for (vector<bool>::const_iterator bought = productList.begin(); bought != productList.end(); bought++)
			if (*bought)
				productHistogram.at(bought - productList.begin()) += 1;
	}

	return productHistogram;
}

Advertising::Advertising(Clients * clients, Products * products, Transactions * transactions) :
	clients(clients),
	products(products),
	transactions(transactions)
{
	// Empty block
}

Product Advertising::getAdvertising(unsigned int clientId)
{
	vector<vector<bool>> matrix = computeBoolMatrix();
	vector<unsigned int> productsCount = computeProductsCount();
	unsigned int clientIndex = clients->getClientIndex(clientId);
	vector<bool> clientProducts = matrix.at(clientIndex);

	unsigned int maxComonProducts = 0;
	unsigned int commonClientIndex = clientIndex;
	for (vector<vector<bool>>::const_iterator client = matrix.begin(); client != matrix.end(); client++)
	{
		unsigned int commonProducts = 0;
		// Continue if hits the client we want to advertise row
		if (client - matrix.begin() == clientIndex)
			continue;
	
		for (int i = 0; i < products->size(); i++)
			if (client->at(i) && clientProducts.at(i))
				commonProducts += 1;

		unsigned int curClientNProducts = getNumberOfProductsBought(*client);
		unsigned int askedClientNProducts = getNumberOfProductsBought(clientProducts);
		if (commonProducts > maxComonProducts && curClientNProducts > askedClientNProducts)
		{
			maxComonProducts = commonProducts;
			commonClientIndex = client - matrix.begin();
		}
	}
	// If no one has anything in common with provided user or has bought less, returns empty product
	if (commonClientIndex == clientIndex)
		return Product("", 0);

	vector<bool> recommended = matrix.at(commonClientIndex);
	// Removes all common products from recommended
	for (int i = 0; i > recommended.size(); i++)
		if (clientProducts.at(i))
			recommended.at(i) = false;

	unsigned int pIndex = 0;
	unsigned int count = 0;
	for (int i = 0; i < recommended.size(); i++)
		if (recommended.at(i))
			if (count < productsCount.at(i))
			{
				count = productsCount.at(i);
				pIndex = i;
			}
	if (count == 0)
		return Product("", 0);

	return products->getProduct(pIndex);
}

Product Advertising::getAdvertising(vector<Client> ClientList)
{
	vector<vector<bool>> matrix = computeBoolMatrix();
	vector<unsigned int> clientIndex;
	vector<bool> clientsProducts;
	clientsProducts.resize(products->size(), false);

	for (vector<Client>::const_iterator it = ClientList.begin(); it != ClientList.end(); it++)
		clientIndex.push_back(clients->getClientIndex(it->getId()));

	for (int productIndex = 0; productIndex < products->size(); productIndex++)
	{
		bool allBought = true;
		for (vector<unsigned int>::const_iterator client = clientIndex.begin(); client != clientIndex.end(); client++)
		{
			if (!matrix.at(*client).at(productIndex))
			{
				allBought = false;
				break;
			}
			clientsProducts.at(productIndex) = allBought;
		}
	}


	vector<unsigned int> commonClients;
	for (unsigned int client = 0; client < matrix.size(); client++)
	{
		bool common = true;
		vector<bool> productList = matrix.at(client);
		for (unsigned productIndex = 0; productIndex < productList.size(); productIndex++)
		{
			if (clientsProducts.at(productIndex) && !productList.at(productIndex))
			{
				common = false;
				break;
			}
		}
		if (common)
			commonClients.push_back(client);
	}

	unsigned int maxCount = 0;
	unsigned int maxIndex = 0;
	vector<unsigned int> histogram = calculateHistogram(commonClients);
	for (int p = 0; p < histogram.size(); p++)
		if (histogram.at(p) > maxCount)
		{
			maxCount = histogram.at(p);
			maxIndex = p;
		}

	if (maxCount != 0)
		return products->getProduct(maxIndex);

	return Product("", 0);
}
