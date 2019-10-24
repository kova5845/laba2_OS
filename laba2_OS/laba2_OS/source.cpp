#include <iostream>
#include <vector>
#include "sourse.h"
#include <fstream>
#include <Windows.h>
#include <ctime>

using namespace std;


double Table::getX()
{
	return vector_x.back();
}

double Table::getY()
{
	return vector_y.back();
}

void Table::setX(double x)
{
	vector_x.push_back(x);
}

void Table::setY(double y)
{
	vector_y.push_back(y);
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

Member::Member(Table* table, Point* point, SYSTEMTIME** st) {
	this->table = table;
	this->point = point;
	this->st = st;
}

DWORD WINAPI count_func(LPVOID ptr)
{
	//Member* member = (Member*)(ptr);
	Member* member = reinterpret_cast<Member*>(ptr);
	double x = 0;
	double h = 0.1;
	while (x<100)
	{
		member->table->setX(x);
		member->table->setY(x);
		GetLocalTime(member->st[0]);
		cout << x << "  " << x << "  " << member->st[0]->wSecond << endl;
		x += h;
	}

	return (0);
}

DWORD WINAPI write_in_file(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	ofstream fout;
	fout.open("file.txt");
	fout << member->table->getX() << " " << member->table->getY() << "\n";
	GetLocalTime(member->st[1]);
	fout.close();

	return (0);
}

DWORD WINAPI write_in_Point(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	member->point->setX(member->table->getX());
	member->point->setX(member->table->getY());
	GetLocalTime(member->st[2]);

	return (0);
}

DWORD WINAPI write_log(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	ofstream fout;

	fout.open("file.log");
	fout << member->st[0]->wHour
		<< member->st[0]->wMinute
		<< member->st[0]->wSecond
		<< member->st[0]->wMilliseconds
		<< " "
		<< member->st[1]->wHour
		<< member->st[1]->wMinute
		<< member->st[1]->wSecond
		<< member->st[1]->wMilliseconds
		<< " "
		<< member->st[2]->wHour
		<< member->st[2]->wMinute
		<< member->st[2]->wSecond
		<< member->st[2]->wMilliseconds
		<< "\n";
	fout.close();

	return (0);
}