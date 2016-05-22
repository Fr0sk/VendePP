/*
* Grupo: T7G03
*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

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
	vector<Client> clients_sorted_by_amoutPaid;
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
	void SortClientsByAmountPaid();
	vector<Client> CalculateBottom10();
	unsigned int getClientIndex(unsigned int clientId);
	bool exists(unsigned int clientId);
};

bool nameOrder(Client left, Client right);
bool cmd(const Client & c1, const Client & c2);
