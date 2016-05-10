#pragma once
#include "Client.h"
#include "Database.h"
#include "Product.h"

#include <string>
#include <vector>

using namespace std;

class Clients
{
private:
	vector<Client> clients;
	Database database;
	
	void setupDatabase(string path);
	void load();
	void save();
	//bool nameOrder(Product * left, Product * right);
public:
	Clients(string databasePath);
	unsigned int size();
	bool printClient(unsigned int clientId);
	void dump();
	void list();
	void addClient(Client client);
	void editClient(unsigned int clientId, string name, double amountPaid);
	bool removeClient(unsigned int id);
	Client getClient(unsigned int clientId);
	Client getClient(string name);
	unsigned int getLastId() const;
};

bool nameOrder(Client left, Client right);

