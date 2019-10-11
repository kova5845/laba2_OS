#include <iostream>
#include <vector>
#include "sourse.h"
#include <fstream>
#include <Windows.h>
using namespace std;


double Table::getX()
{
	return x.back();
}

double Table::getY()
{
	return y.back();
}

void Table::setX(double x)
{
	this->x.insert(this->x.end(), x);
}

void Table::setY(double y)
{
	this->y.insert(this->y.end(), y);
}


double Point :: getX() 
{
	return x;
}

double Point :: getY() 
{
	return y;
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

void write_log(Table* t, Point* p, SYSTEMTIME* st)
{
	ofstream fout;
	fout.open("file.log");
	fout << st[0].wHour
		<< st[0].wMinute
		<< st[0].wSecond
		<< st[0].wMilliseconds
		<< " "
		<< st[1].wHour
		<< st[1].wMinute
		<< st[1].wSecond
		<< st[1].wMilliseconds
		<< " "
		<< st[2].wHour
		<< st[2].wMinute
		<< st[2].wSecond
		<< st[2].wMilliseconds
		<< "\n";
	fout.close();
}

void count_func(Table* t, Point* p, SYSTEMTIME* st)
{
	double x = 0;
	double h = 0.1;
	while (true)
	{
		t->setX(x);
		t->setY(x);
		GetLocalTime(&st[0]);
		x += h;
	}
}

void write_in_file(Table* t, Point* p, SYSTEMTIME* st)
{
	ofstream fout;
	fout.open("file.txt");
	fout << t->getX() << " " << t->getY() << "\n";
	GetLocalTime(&st[1]);
	fout.close();
}

void write_in_Point(Table* t, Point* p, SYSTEMTIME* st)
{
	p->setX(t->getX());
	p->setY(t->getY());
	GetLocalTime(&st[2]);	
}