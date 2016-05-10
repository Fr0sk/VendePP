#include "Advertising.h"

Advertising::Advertising(Clients * clients, Products * products, Transactions * transactions) :
	clients(clients),
	products(products),
	transactions(transactions)
{
	// Empty block
}

vector<unsigned int> Advertising::getAdvertising(unsigned int clientId)
{
	vector<unsigned int> recommended;
	vector<vector<bool>> matrix;

	// Creates a matrix with nClients rows and nProducts columns, initialized with false
	matrix.resize((*clients).size(), vector<bool>((*products).size(), false));

	for (unsigned int tId = 1; tId < (*transactions).size(); tId++)
	{
		/*Transaction transaction = (*transactions).getTransaction(tId);

		// Products listen in the transaction
		vector<unsigned int> productIds;
		vector<Product> transactionProducts = transaction.getProducts();
		for (vector<Product>::const_iterator pIt = transactionProducts.begin(); pIt != transactionProducts.end(); pIt++)
			productIds.push_back((*pIt))

		// The row of the client in the transaction
		vector<bool> row = matrix.at(transaction.getClientId() - 1);

		// Sets all the products in the transaction to true
		for (vector<unsigned int>::iterator it = productIds.begin(); it != productIds.end(); it++)
			row.at((*it) - 1) = true;

		// Updates the row
		matrix.at(transaction.getClientId() - 1) = row;*/
	}

	unsigned int maxCommon = 0;
	unsigned int commonClientId = 0;

	for (vector<vector<bool>>::iterator c = matrix.begin(); c != matrix.end(); c++)
	{
		// Does not compare the client with himself
		if (!(c - matrix.begin() + 1 == clientId))
		{
			unsigned int currentCommon = 0;
			for (vector<bool>::iterator p = (*c).begin(); p != (*c).end(); p++)
			{
				// If its common, increases the counter
				if (*p)
					currentCommon++;
			}
			// Updates the maxCommon
			if (currentCommon > maxCommon)
			{
				maxCommon = currentCommon;
				commonClientId = c - matrix.begin() + 1;
			}
		}
	}

	if (commonClientId == 0)
		return recommended;

	// Populates recommended vector with recommended products
	for (vector<bool>::iterator p = matrix.at(commonClientId - 1).begin(); p != matrix.at(commonClientId - 1).end(); p++)
	{
		// If the current value is true and the client value isn't
		if (*p && !matrix.at(clientId - 1).at(p - matrix.at(commonClientId - 1).begin()))
			recommended.push_back(p - matrix.at(commonClientId - 1).begin() + 1);
	}

	return recommended;
}
