#include "Transaction.h"

Transaction::Transaction(unsigned int clientId, Date date, vector<Product> products) :
	clientId(clientId),
	date(date),
	products(products)
{
}

unsigned int Transaction::getClientId() const
{
	return clientId;
}

Date Transaction::getDate() const
{
	return date;
}

vector<Product> Transaction::getProducts() const
{
	return products;
}
