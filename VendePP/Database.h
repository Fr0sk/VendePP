#pragma once
#include <string>
#include <vector>

using namespace std;

class Database
{
private:
	string path;
	unsigned int params;
public:
	Database();
	Database(string path, unsigned int params);
	void setPath(string value);
	void setParams(unsigned int value);
	void read(vector<string> & values);
	void write(vector<string> & values) const;
};

