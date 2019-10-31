#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

const int THREADCOUNT = 4;
const int EVENTCOUNT = 4;
extern HANDLE ghEvent[EVENTCOUNT];


class Table
{
	vector <double> vector_x;
	vector <double> vector_y;

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

class Member
{

public:
	Table* table;
	Point* point;
	SYSTEMTIME** st;

public:
	Member(Table* table, Point* point, SYSTEMTIME** st);

};

DWORD WINAPI write_log(PVOID ptr);
DWORD WINAPI write_in_Point(PVOID ptr);
DWORD WINAPI write_in_file(PVOID ptr);
DWORD WINAPI count_func(PVOID ptr);