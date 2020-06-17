#pragma once

#include <iostream>
#include <string>
#include "cached_map.h"

using namespace std;

class employee
{
public:
	employee() : _id("         "), _salary(NULL), _seniority(NULL) {}
	employee(string id, int salary, int seniority) : _id(id), _salary(salary), _seniority(seniority) {}
	employee* load(istream& in);
	string getId() { return _id; }
	int getSalary() { return _salary; }
	int getSeniority() { return _seniority; }
	friend bool operator==(string a, string b);
	friend ostream& operator<< (ostream& out, employee* E);
	
	

private:
	string _id;
	int _salary;
	int _seniority;
};

bool operator==(string a, string b)
{
	return (a._Equal(b));
}

 ostream& operator<< (ostream& out, employee* E)
{
	out << E->getId() << endl;
	out << E->getSalary()<< endl;
	out << E->getSeniority() << endl;
	return out;
}