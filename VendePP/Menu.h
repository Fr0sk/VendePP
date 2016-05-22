/*
* Grupo: T7G03
*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#pragma once
#include "Clients.h"
#include "Products.h"
#include "Transactions.h"
#include "Advertising.h"

#include <string>
#include <vector>

using namespace std;

class Menu
{
private:
	int lineLength;
	int activeMenu;
	vector<string> menuOptions;
	vector<vector<string>> subMenus;
	Clients * clients;
	Products * products;
	Transactions * transactions;
	Advertising * advertising;

	void printBar(bool printNewLine=true) const;
	void printLine(string text, bool printNewLine=true, bool boxed = true, bool clear = false) const;
	void printHeader(string menuText) const;
	void printFooter(bool isSubMenu = false) const;
public:
	Menu(Clients * clients, Products * products, Transactions * transactions, Advertising * advertising);
	void printMenu(unsigned int option);
	int getOption() const;
	int getActiveMenu() const;
	
	void customersAdd();
	void customersView();
	void customersEdit();
	void customersRemove();
	void customersRecommendations();
	void bottom10Recommendations();
	void productsAdd();
	void productsView();
	void transactionsMake();
	void transactionsView();

	// Helper function
	static string toStringWithPrecision(double value, int precision);

	enum Menus {
		MAIN = 0,
		M_CUSTOMERS = 1,
		M_PRODUCTS = 2,
		M_TRANSACTIONS = 3
	};
	enum M_Customers {
		C_ADD = 1,
		C_VIEW = 2,
		C_EDIT = 3,
		C_REMOVE = 4,
		C_ADVERTISING = 5,
		C_BOTTOM_10_ADS = 6
	};
	enum M_Products {
		P_ADD = 1,
		P_VIEW = 2
	};
	enum M_Transactions {
		T_MAKE = 1,
		T_VIEW = 2
	};

	enum ReturnCode {
		RETURN = 0
	};
};
