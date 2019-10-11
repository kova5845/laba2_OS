#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Table
{
	vector <double> x;
	vector <double> y;

public: 
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};

class Point
{
	double x;
	double y;

public:
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};

void write_log(Table* t, Point* p, SYSTEMTIME* st);
void write_in_Point(Table* t, Point* p, SYSTEMTIME* st);
void write_in_file(Table* t, Point* p, SYSTEMTIME* st);
void count_func(Table* t, Point* p, SYSTEMTIME* st);