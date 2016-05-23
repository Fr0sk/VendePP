/*
* Grupo: T7G03
*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#include "Clients.h"
#include "Date.h"

#include <iostream>
#include <algorithm>

void Clients::setupDatabase(string path)
{
	database.setPath(path);
	database.setParams(4);
}

void Clients::load()
{
	vector<string> clientsList;
	database.read(clientsList);

	vector<Client> tmpClients;

	for (vector<string>::iterator it = clientsList.begin() + 1; it != clientsList.end();)
	{
		unsigned int id = std::stoi(*it++);

		string name = (*it++);
		Date joinDate(*it++);
		double amountPaid = std::stod((*it++));
		Client c(id, name, joinDate, amountPaid);
		tmpClients.push_back(c);
	}
	clients.clear();
	clients = tmpClients;
}

void Clients::save()
{
	vector<string> values;
	values.push_back(to_string(size()));

	for (vector<Client>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		values.push_back(std::to_string((*it).getId()));
		values.push_back((*it).getName());
		values.push_back((*it).getJoinDate().toString());
		string spent = std::to_string((*it).getAmountPaid());
		spent = spent.substr(0, spent.find(".") + 3);
		values.push_back(spent);
	}
	database.write(values);
}

Clients::Clients(string databasePath)
{
	setupDatabase(databasePath);
	load();
}

unsigned int Clients::size()
{
	return clients.size();
}

bool Clients::printClient(unsigned int clientId)
{
	Client c = getClient(clientId);
	if (c.getId() == 0)
		cout << "There is no client with ID: " << clientId << endl;
	else {
		cout << "Client: " << c.getId() << endl;
		cout << "\t      Name: " << c.getName() << endl;
		cout << "\t Join Date: " << c.getJoinDate().toString() << endl;
		cout << "\t     Spent: " << c.getAmountPaid() << endl << endl;
		return true;
	}
	return false;
}

void Clients::dump()
{
	for (vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		printClient((*it).getId());
		cout << endl;
	}
}

void Clients::list()
{
	vector<Client> order = clients;
	sort(order.begin(), order.end(), nameOrder);
	for (vector<Client>::iterator it = order.begin(); it != order.end(); it++)
	{
		printClient((*it).getId());
		cout << endl;
	}
}

void Clients::addClient(Client client)
{
	clients.push_back(client);
	save();
}

void Clients::editClient(unsigned int clientId, string name, double payment)
{
	for (vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it).getId() == clientId)
		{
			(*it).setName(name);
			(*it).addPayment(payment);
			save();
			break;
		}
	}
}

bool Clients::removeClient(unsigned int id)
{
	for (vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it).getId() == id)
		{
			clients.erase(it);
			save();
			return true;
		}
	}
	return false;
}

Client Clients::getClient(unsigned int clientId)
{
	for (vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		if ((*it).getId() == clientId)
			return (*it);
	return Client(0, "", Date::createDate(), 0);
}

Client Clients::getClient(string name)
{
	for (vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		if ((*it).getName() == name)
			return (*it);
	return Client(0, "", Date::createDate(), 0);
}

unsigned int Clients::getLastId() const
{
	return clients.at(clients.size() - 1).getId();
}

bool nameOrder(Client left, Client right)
{
	return (left).getName() < (right).getName();
}

//novo
bool cmd(const Client & c1, const Client & c2)
{
	if (c1.getAmountPaid() < c2.getAmountPaid()) return c1.getAmountPaid() < c2.getAmountPaid();
	return c1.getAmountPaid() < c2.getAmountPaid();
}
//novo
void Clients::SortClientsByAmountPaid()
{
	clients_sorted_by_amoutPaid.clear();
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		clients_sorted_by_amoutPaid.push_back(clients[i]);
	}

	sort(clients_sorted_by_amoutPaid.begin(), clients_sorted_by_amoutPaid.end(), cmd);
}
//novo
vector<Client> Clients::CalculateBottom10()
{
	vector<Client> bottom10;

	SortClientsByAmountPaid();

	for (unsigned int i = 0; i < 10; i++)
	{
		if (i == clients_sorted_by_amoutPaid.size())
			break;
		else
			bottom10.push_back((clients_sorted_by_amoutPaid[i]));
	}
	return bottom10;
}

unsigned int Clients::getClientIndex(unsigned int clientId)
{
	for (int i = 0; i < clients.size(); i++)
		if (clients.at(i).getId() == clientId)
			return i;
	return clients.size();
}

bool Clients::exists(unsigned int clientId)
{
	for (int i = 0; i < clients.size(); i++)
		if (clients.at(i).getId() == clientId)
			return true;
	return false;
}
