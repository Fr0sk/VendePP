/*
* Grupo: T7G03*
* Filipe Coelho - 201500072
* Luís Cruz - 201303248
*/

#include "Database.h"

#include <iostream>
#include <fstream>

using namespace std;

Database::Database()
{
	// Empty block
}

Database::Database(string path, unsigned int params) :
	path(path),
	params(params)
{
	// Empty block
}

void Database::setPath(string value)
{
	path = value;
}

void Database::setParams(unsigned int value)
{
	if (params != value)
		params = value;
}

void Database::read(vector<string> & values)
{
	ifstream inStream;
	string line;
	inStream.open(path);
	
	getline(inStream, line);
	values.push_back(line);
	while (getline(inStream, line))
	{
		for (unsigned int i = 0; i < params - 1; i++)
		{
			values.push_back(line.substr(0, line.find(";") - 1));
			line = line.substr(line.find(";") + 2);
		}
		values.push_back(line);
	}

	inStream.close();
}

void Database::write(vector<string> &values) const
{
	ofstream outStream;
	outStream.open(path);

	outStream << values.at(0);

	for (vector<string>::const_iterator it = values.begin() + 1; it != values.end();)
	{
		string tmp = (*it++);
		for (unsigned int i = 0; i < params - 1; i++)
			tmp += " ; " + (*it++);
		outStream << endl << tmp;
	}

	outStream.close();
}
