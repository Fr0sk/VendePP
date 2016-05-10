#include "Menu.h"
#include "Clients.h"
#include "Products.h"
#include "Transactions.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

void Menu::printBar(bool printNewLine) const
{
	for (int i = 0; i < lineLength; i++)
		cout << "#";

	if (printNewLine)
		cout << endl;
}

void Menu::printLine(string text, bool printNewLine, bool boxed, bool clear) const
{
	if (clear)
		system("cls");

	if (boxed)
	{
		cout << "# " << text << " ";
		for (int i = text.length() + 4; i < lineLength; i++)
			cout << " ";
		cout << "#";
	}
	else
		cout << text;

	if (printNewLine)
		cout << endl;

}

void Menu::printHeader(string menuText) const
{
	printBar();
	printLine("Vende++ - Supermarkets");
	printBar();
	printLine("");
	printLine(menuText + ":");
	printLine("");
}

void Menu::printFooter(bool isSubMenu) const
{
	printLine("");
	if (isSubMenu)
		printLine("0 - Return to Main Menu");
	else
		printLine("0 - Quit Program");

	printLine("");
	printBar();
}

Menu::Menu(Clients * clients, Products * products, Transactions * transactions, Advertising * advertising) :
	lineLength(30),
	activeMenu(0),
	clients(clients),
	products(products),
	transactions(transactions),
	advertising(advertising)
{
	menuOptions.push_back("Manage Customers");
	menuOptions.push_back("Manage Products");
	menuOptions.push_back("Manage Transactions");

	vector<string> manageCustomers;
	manageCustomers.push_back("Add Customer");
	manageCustomers.push_back("View Customer");
	manageCustomers.push_back("Edit Customer");
	manageCustomers.push_back("Remove Customer");
	manageCustomers.push_back("Get Recommendations");

	vector<string> manageProducts;
	manageProducts.push_back("Add Product");
	manageProducts.push_back("View Product");
	manageProducts.push_back("Edit Product");

	vector<string> manageTransactions;
	manageTransactions.push_back("Make Transaction");
	manageTransactions.push_back("View Transactions");

	subMenus.push_back(manageCustomers);
	subMenus.push_back(manageProducts);
	subMenus.push_back(manageTransactions);

	setprecision(2);
}

void Menu::printMenu(unsigned int option)
{
	system("cls");

	if (option < 0 || option > subMenus.size())
		option = activeMenu;

	if (option == 0)
	{
		// Print Main Menu
		printHeader("Menu");

		for (vector<string>::const_iterator it = menuOptions.begin(); it != menuOptions.end(); it++)
		{
			stringstream ss;
			int optNumber = it - menuOptions.begin() + 1;
			ss << optNumber << " - " << (*it);
			printLine(ss.str());
		}

		printFooter();
		activeMenu = option;
	}
	else
	{
		// Print Sub Menu
		unsigned int index = option - 1;
		printHeader(menuOptions[index]);

		vector<string> subMenu = subMenus[index];
		for (vector<string>::const_iterator it = subMenu.begin(); it != subMenu.end(); it++)
		{
			stringstream ss;
			int optNumber = it - subMenu.begin() + 1;
			ss << optNumber << " - " << (*it);
			printLine(ss.str());
		}

		printFooter(true);

	}
	activeMenu = option;
}

int Menu::getOption() const
{
	cout << "Please select an option: ";
	int opt;
	cin >> opt;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		opt = -1;
	}
	return opt;
}

int Menu::getActiveMenu() const
{
	return activeMenu;
}

void Menu::customersAdd()
{
	string idString = std::to_string((*clients).getLastId() + 1), name, dateString = Date::createDate().toString();

	cin.clear();
	cin.ignore(10000, '\n');

	printLine("Enter customer ID (Enter for " + idString + "): ", false, false, true);
	getline(cin, idString);
	if (idString.size() == 0)
		idString = std::to_string((*clients).getLastId() + 1);
	if ((*clients).getClient(std::stoi(idString)).getId() != 0)
	{
		printLine("ID already in use!", true, false, false);
		cin.clear();
		cin.ignore(10000, '\n');
		return;
	}

	printLine("Enter customer name: ", false, false, false);
	getline(cin, name);

	printLine("Enter custom date (Enter for " + dateString + "): ", false, false, false);
	getline(cin, dateString);
	if (dateString.size() == 0)
		dateString = Date::createDate().toString();

	unsigned int id = std::stoul(idString);
	Date date(dateString);
	Client c(id, name, date, 0.0);
	(*clients).addClient(c);
	printLine("Client created!", true, false, true);
	(*clients).printClient(id);

	system("pause");
}

void Menu::customersView()
{
	string input;
	string info = "Enter customer ID (Enter '*' for all by Name): ";

	printLine(info, false, false, true);

	cin >> input;
	if (input.find("*") == 0)
	{
		(*clients).list();
	}
	else {
		unsigned int id = (unsigned int)std::abs(std::stoi(input));
		(*clients).printClient(id);
	}
	system("pause");
}

void Menu::customersEdit()
{
	string input;
	string info = "Enter customer ID: ";

	printLine(info, false, false, true);

	cin >> input;
	unsigned int id = (unsigned int)std::abs(std::stoi(input));
	if (!(*clients).printClient(id))
	{
		system("pause");
		return;
	}
	Client c = (*clients).getClient(id);
	string name = c.getName();
	double amoutPaid = c.getAmountPaid();
	double payment = 0;

	cout << endl;
	printBar(true);
	printLine("");
	printLine("1 - Edit name");
	printLine("2 - Add payment");
	printLine("");
	printBar(true);

	printLine("Please select an option: ", false, false, false);
	int option;
	if (!(cin >> option))
	{
		printLine("Invalid option", false, false, false);
		cin.clear();
		cin.ignore(10000, '\n');
		return;
	}
	cin.clear();
	cin.ignore(10000, '\n');

	switch (option)
	{
	case 1:
		printLine("Enter new name: ", false, false, true);
		getline(cin, name);
		break;
	case 2:
		printLine("Enter amout to add to total (current " + to_string(amoutPaid) + "): "
			, false, false, true);
		if (!(cin >> payment))
			printLine("Invalid amount!", false, false, false);
		break;
	default:
		printLine("Invalid option", false, false, false);
		break;
	}

	(*clients).editClient(id, name, payment);

	printLine("Client updated!", true, false, true);
	(*clients).printClient(id);
	system("pause");
}

void Menu::customersRemove()
{
	unsigned int id;
	string info = "Enter customer ID: ";
	printLine(info, false, false, true);
	if (!(cin >> id))
		printLine("Invalid ID", true, false, false);
	else if ((*clients).getClient(id).getId() == 0)
		printLine("There is no client with that ID", true, false, false);
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		string choice;

		(*clients).printClient(id);
		printLine("Do you wish to remove this client? (Y - Yes; N - No): ", false, false, false);
		getline(cin, choice);

		if (choice == "Y" || choice == "y")
		{
			if ((*clients).removeClient(id))
				printLine("Client removed!", true, false, false);
			else
				printLine("Client couldn't be removed!", true, false, false);
		}
		else {
			printLine("Client not removed!", true, false, false);
		}
	}
	
	system("pause");
}

void Menu::customersRecommendations()
{
	// TODO Recomendações
	/*unsigned int id;
	string info = "Enter customer ID: ";
	printLine(info, false, false, true);
	if (!(cin >> id))
		printLine("Invalid option", true, false, false);
	else if (id == 0 || id > (*clients).size())
		printLine("There is no client with that ID!", true, false, false);
	else {
		// Prints the client
		printLine("", true, false, false);
		(*clients).printClient(id);

		vector<unsigned int> productIds = (*advertising).getAdvertising(id);
		if (productIds.size() == 0)
			printLine("There is no recommendation for this client!", true, false, false);
		else {
			printLine("\tRecommendations:", true, false, false);

			for (vector<unsigned int>::iterator it = productIds.begin(); it != productIds.end(); it++)
			{
				Product p = (*products).getProduct(*it);
				printLine("\t\t" + p.getName() , true, false, false);
			}
		}
	}*/

	system("pause");
}

void Menu::productsAdd()
{
	string name;
	double price;
	cin.clear();
	cin.ignore(10000, '\n');

	printLine("Enter product name: ", false, false, true);
	getline(cin, name);

	printLine("Enter product price: ", false, false, false);
	if (!(cin >> price))
	{
		printLine("Invalid amount!", false, false, false);
		return;
	}

	(*products).addProduct(name, price);
	printLine("Product created!", true, false, true);
	(*products).printProduct((*products).size());

	system("pause");
}

void Menu::productsView()
{
	string input;
	string info = "Enter product ID (* for all): ";

	printLine(info, false, false, true);

	cin >> input;
	if (input.find("*") == 0)
	{
		(*products).dump();
	}
	else {
		unsigned int id = (unsigned int)std::abs(std::stoi(input));
		(*products).printProduct(id);
	}
	system("pause");
}

void Menu::transactionsMake()
{
	unsigned int clientId;
	double payment = 0;
	string input;
	vector<Product>productList;
	cin.clear();
	cin.ignore(10000, '\n');

	printLine("Enter client ID: ", false, false, true);
	if (!(cin >> clientId) || (*clients).getClient(clientId).getId() == 0)
	{
		printLine("Invalid client ID!", true, false, false);
		system("pause");
		return;
	}

	cin.clear();
	cin.ignore(10000, '\n');

	printLine("Total: " + toStringWithPrecision(payment, 2), true, false, false);
	printLine("Enter product names (0 to exit): ", false, false, false);
	getline(cin, input);

	while (input != "0")
	{
		Product p = (*products).getProduct(input);
		if (p.getName() != "")
		{
			productList.push_back(p);
			payment += p.getPrice();
			printLine(p.getName() + " added at price: " + toStringWithPrecision(p.getPrice(), 2), true, false, true);
		} else {
			printLine("Product " + input + " not found!", true, false, true);
		}
		system("pause");

		printLine("Total: " + toStringWithPrecision(payment, 2), true, false, true);
		printLine("Enter product names (0 to exit): ", false, false, false);
		getline(cin, input);
	}


	if (productList.size() == 0)
	{
		printLine("Invalid products", true, false, false);
		system("pause");
		return;
	}

	// Create transaction
	(*transactions).addTransaction(clientId, productList);

	// Update client
	Client c = (*clients).getClient(clientId);
	(*clients).editClient(c.getId(), c.getName(), payment);

	printLine("Transaction made!", true, false, true);
	(*transactions).printTransaction((*transactions).size() - 1);
	system("pause");
}

void Menu::transactionsView()
{
	system("cls");
	printBar(true);
	printLine("");
	printLine("View Transactions:");
	printLine("1 - By Index");
	printLine("2 - By Client");
	printLine("3 - By Date");
	printLine("4 - Between two dates");
	printLine("5 - All");
	printLine("");
	printBar(true);

	printLine("Please select an option: ", false, false, false);
	int option;
	unsigned int id = 0, day = 0, month = 0, year = 0, day2 = 0, month2 = 0, year2 = 0;
	string name;
	if (!(cin >> option))
	{
		printLine("Invalid option", false, false, false);
		cin.clear();
		cin.ignore(10000, '\n');
		return;
	}
	cin.clear();
	cin.ignore(10000, '\n');

	switch (option)
	{
	case 1:
	{
		printLine("Enter transaction ID: ", false, false, true);

		if (!(cin >> id))
			printLine("Invalid option", true, false, false);
		else if (!(*transactions).printTransaction(id))
			printLine("", true, false, false);
		break;
	}
	case 2:
	{
		printLine("Enter client name: ", false, false, true);
		getline(cin, name);
		Client c = (*clients).getClient(name);
		if (c.getId() == 0)
			printLine("No client found with that name", true, false, false);
		else if (!(*transactions).printTransaction(c))
			printLine("No transaction found for this client ", true, false, false);
		break;
	}
	case 3:
	{
		printLine("Enter day: ", false, false, true);
		if (!(cin >> day) || day == 0 || day > 31)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		printLine("Enter month: ", false, false, true);
		if (!(cin >> month) || month == 0 || month > 12)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		printLine("Enter year: ", false, false, true);
		if (!(cin >> year) || year == 0)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		Date date = Date::createDate(day, month, year);
		if (!(*transactions).printTransaction(date))
			printLine("There are no transactions in that date", false, false, false);
		break;
	}
	case 4:
	{
		printLine("Enter beginning day: ", false, false, true);
		if (!(cin >> day) || day > 31)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		// Date 1 Input
		printLine("Enter beginning month: ", false, false, true);
		if (!(cin >> month) || month > 12)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		printLine("Enter beginning year: ", false, false, true);
		if (!(cin >> year))
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		// Date 2 Input
		printLine("Enter ending day: ", false, false, true);
		if (!(cin >> day2) || day2 == 0 || day2 > 31)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		printLine("Enter ending month: ", false, false, true);
		if (!(cin >> month2) || month2 == 0 || month2 > 12)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		printLine("Enter ending year: ", false, false, true);
		if (!(cin >> year2) || year2 == 0)
		{
			printLine("Invalid option", false, false, false);
			break;
		}

		Date dateStart = Date::createDate(day, month, year);
		Date dateEnd = Date::createDate(day2, month2, year2);
		if (!(*transactions).printTransaction(dateStart, dateEnd))
			printLine("There are no transactions between those dates", false, false, false);
		break;
	}
	case 5:
		(*transactions).dump();
		break;
	default:
		printLine("Invalid option", false, false, false);
		break;
	}
	system("pause");
}


string Menu::toStringWithPrecision(double value, int precision)
{
	string tmp = to_string(value);
	if (tmp.find(".") != string::npos)
		tmp = tmp.substr(0, tmp.find(".") + precision + 1);
	return tmp;
}
