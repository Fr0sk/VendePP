/*
* Grupo: T7G03*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#include "Transactions.h"

#include <iostream>

void Transactions::setupDatabase(string path)
{
	database.setPath(path);
	database.setParams(3);
}

void Transactions::load()
{
	vector<string> transactionList;
	database.read(transactionList);

	vector<Transaction> tmpTransactions;

	for (vector<string>::iterator it = transactionList.begin() + 1; it != transactionList.end(); it++)
	{
		unsigned int client = std::stoi(*it++);
		Date date(*it++);
		string productList = (*it);

		vector<Product> p;
		string name = (productList.find(",") != string::npos) ? productList.substr(0, productList.find(",")) : productList;
		p.push_back((*products).getProduct(name));
		
		while (productList.find(",") != string::npos)
		{
			productList = productList.substr(productList.find(",") + 2);
			name = (productList.find(",") != string::npos) ? productList.substr(0, productList.find(",")) : productList;
			p.push_back((*products).getProduct(name));
		}
		
		Transaction transaction(client, date, p);
		tmpTransactions.push_back(transaction);
	}

	transactions.clear();
	transactions = tmpTransactions;
}

void Transactions::save()
{
	vector<string> values;
	values.push_back(to_string(size()));

	string line;
	for (vector<Transaction>::const_iterator transaction = transactions.begin(); transaction != transactions.end(); transaction++)
	{
		values.push_back(to_string((*transaction).getClientId()));
		values.push_back((*transaction).getDate().toString());
		
		line = (*transaction).getProducts().at(0).getName();
		vector<Product> productList = (*transaction).getProducts();
		for (vector<Product>::const_iterator product = productList.begin() + 1; product != productList.end(); product++)
			line += ", " + (*product).getName();
		values.push_back(line);
	}
	database.write(values);
}

Transactions::Transactions(string databasePath, Clients * clients, Products * products) :
	clients(clients),
	products(products)
{
	setupDatabase(databasePath);
	load();
}

unsigned int Transactions::size()
{
	return transactions.size();
}

bool Transactions::printTransaction(unsigned int index)
{
	if (index >= transactions.size())
		cout << "There is no transaction with index: " << index << endl;
	else {
		Transaction transaction = transactions.at(index);
		Client c = (*clients).getClient(transaction.getClientId());
		vector<Product> ps;

		cout << "Transaction: " << endl;
		cout << "\t  Client: (" << c.getId() << ") " << c.getName() << endl;
		cout << "\tProducts:" << endl;

		vector<Product> p = transaction.getProducts();
		for (vector<Product>::iterator it = p.begin(); it != p.end(); it++)
		{
			cout << "\t\t" << (*it).getName() << "(" << (*it).getPrice() << ")" << endl;
		}
		return true;
	}
	return false;
}

bool Transactions::printTransaction(Client client)
{
	bool found = false;

	for (vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); it++)
	{
		if ((*it).getClientId() == client.getId())
		{
			if (found)
				cout << endl;
			printTransaction(it - transactions.begin());
			found = true;
		}
	}

	return found;
}

bool Transactions::printTransaction(Date date)
{
	bool found = false;

	for (vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); it++)
	{
		if ((*it).getDate() == date)
		{
			if (found)
				cout << endl;
			printTransaction(it - transactions.begin());
			found = true;
		}
	}

	return found;
}

bool Transactions::printTransaction(Date start, Date end)
{
	bool found = false;

	for (vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); it++)
	{
		if (start == (*it).getDate() ||
			(start < (*it).getDate() && (*it).getDate() < end) ||
			(*it).getDate() == end)
		{
			if (found)
				cout << endl;
			printTransaction(it - transactions.begin());
			found = true;
		}
	}

	return found;
}

void Transactions::dump()
{
	for (unsigned int i = 0; i < transactions.size(); i++)
	{
		printTransaction(i);
		cout << endl;
	}
}

void Transactions::addTransaction(unsigned int clientId, vector<Product> productList)
{
	Transaction transaction(clientId, Date::createDate(), productList);
	transactions.push_back(transaction);
	save();
}

Transaction Transactions::getTransaction(unsigned int index)
{
	return transactions.at(index);
}
