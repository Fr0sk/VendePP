#pragma once
#include "Transaction.h"
#include "Database.h"
#include "Clients.h"
#include "Products.h"
#include "Client.h"
#include "Date.h"

#include <string>
#include <vector>

using namespace std;

class Transactions
{
private:
	vector<Transaction> transactions;
	Database database;
	Clients * clients;
	Products * products;

	void setupDatabase(string path);
	void load();
	void save();
public:
	Transactions(string databasePath, Clients * clients, Products * products);
	unsigned int size();	
	bool printTransaction(unsigned int index);
	bool printTransaction(Client client);
	bool printTransaction(Date date);
	bool printTransaction(Date start, Date end);
	void dump();
	void addTransaction(unsigned int clientId, vector<Product> products);
	Transaction getTransaction(unsigned int index);
};

