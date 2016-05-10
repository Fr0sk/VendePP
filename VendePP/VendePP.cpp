#include "Menu.h"
#include "Clients.h"
#include "Products.h"
#include "Transactions.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void menuOperations(Menu menu)
{
	static int option = 0;
	menu.printMenu(option);
	option = menu.getOption();
	string input;

	switch (menu.getActiveMenu())
	{
	case Menu::MAIN:
	{
		switch (option)
		{
		case Menu::ReturnCode::RETURN:
			exit(0);
		}
		break;
	}
	case Menu::M_CUSTOMERS:

		switch (option)
		{
		case Menu::M_Customers::C_ADD:
			menu.customersAdd();
			break;
		case Menu::M_Customers::C_VIEW:
			menu.customersView();
			break;
		case Menu::M_Customers::C_EDIT:
			menu.customersEdit();
			break;
		case Menu::M_Customers::C_REMOVE:
			menu.customersRemove();
			break;
		case Menu::M_Customers::C_RECOMMENDATIONS:
			menu.customersRecommendations();
			break;
		}
		break;

	case Menu::M_PRODUCTS:
		switch (option)
		{
		case Menu::M_Products::P_ADD:
			menu.productsAdd();
			break;
		case Menu::M_Products::P_VIEW:
			menu.productsView();
			break;
		}
		break;

	case Menu::M_TRANSACTIONS:
		switch (option)
		{
		case Menu::M_Transactions::T_MAKE:
			menu.transactionsMake();
			break;
		case Menu::M_Transactions::T_VIEW:
			menu.transactionsView();
			break;
		}
		break;
	}

	if (menu.getActiveMenu() != Menu::MAIN && option != Menu::ReturnCode::RETURN)
		option = menu.getActiveMenu();
}

bool fileExists(string fileName)
{
	ifstream inStream(fileName);
	bool exists = false;
	if (inStream)
		return true;
	return false;
}

int main()
{
	string clientsFile = "clients.txt", productsFile = "products.txt", transactionsFile = "transactions.txt";
	/*cout << "Enter clients file name: ";
	getline(cin, clientsFile);
	if (!fileExists(clientsFile))
	{
		cout << "File not found!" << endl;
		system("pause");
		return 1;
	}

	cout << "Enter products file name: ";
	getline(cin, productsFile);
	if (!fileExists(productsFile))
	{
		cout << "File not found!" << endl;
		system("pause");
		return 2;
	}

	cout << "Enter transactions file name: ";
	getline(cin, transactionsFile);
	if (!fileExists(transactionsFile))
	{
		cout << "File not found!" << endl;
		system("pause");
		return 3;
	}*/

	Clients * clients = new Clients(clientsFile);
	Products * products = new Products(productsFile);
	Transactions * transactions = new Transactions(transactionsFile, clients, products);
	Advertising * advertising = new Advertising(clients, products, transactions);

	Menu * menu = new Menu(clients, products, transactions, advertising);

	while (true)
		menuOperations((*menu));
}