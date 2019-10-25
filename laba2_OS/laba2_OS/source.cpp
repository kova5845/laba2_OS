#include <iostream>
#include <vector>
#include "sourse.h"
#include <fstream>
#include <Windows.h>
#include <ctime>

using namespace std;

extern HANDLE ghMutex;
bool FIRST = true;
bool SECOND = false;
bool THIRD = false;
bool FORTH = false;

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
	Member* member = reinterpret_cast<Member*>(ptr);
	DWORD dwWaitResult;
	double x = 0;
	double h = 0.1;
	while (true)
	{
		if (FIRST)
		{
			dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0:

				member->table->setX(x);
				member->table->setY(x);
				GetLocalTime(member->st[0]);
				cout << x << "  " << x << "  " << member->st[0]->wSecond << endl;
				x += h;
				FIRST = false;
				SECOND = true;
				if (!ReleaseMutex(ghMutex))
				{
					cout << "ERROR count_func";
				}

				break;
			case WAIT_ABANDONED:
				return FALSE;
			}
		}
	}

	return TRUE;
}

DWORD WINAPI write_in_file(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	DWORD dwWaitResult;
	ofstream fout;
	fout.open("file.txt", ios_base::trunc);
	fout.close();
	while (true)
	{
		if (SECOND)
		{
			dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
			switch (dwWaitResult)
			{

			case WAIT_OBJECT_0:
				fout.open("file.txt", ios_base::app);
				fout << member->table->getX() << " " << member->table->getY() << "\n";
				GetLocalTime(member->st[1]);
				fout.close();
				SECOND = false;
				THIRD = true;
				if (!ReleaseMutex(ghMutex))
				{
					cout << "ERROR write_in_file";
				}
				break;
			case WAIT_ABANDONED:
				return FALSE;
			}
		}
	}

	return TRUE;
}

DWORD WINAPI write_in_Point(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	DWORD dwWaitResult;
	
	while (true)
	{
		if (THIRD)
		{
			dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0:
				member->point->setX(member->table->getX());
				member->point->setX(member->table->getY());
				GetLocalTime(member->st[2]);
				THIRD = false;
				FORTH = true;
				if (!ReleaseMutex(ghMutex))
				{
					cout << "ERROR write_in_Point";
				}
				break;
			case WAIT_ABANDONED:
				return FALSE;
			}
		}
	}

	return TRUE;
}

DWORD WINAPI write_log(PVOID ptr)
{
	Member* member = reinterpret_cast<Member*>(ptr);
	ofstream fout;
	fout.open("file.log", ios_base::trunc);
	fout.close();
	DWORD dwWaitResult;
	while (true)
	{
		if (FORTH)
		{
			dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0:
				fout.open("file.log", ios_base::app);
				fout << member->st[0]->wMinute << ":"
					<< member->st[0]->wSecond << ":"
					<< member->st[0]->wMilliseconds
					<< " "
					<< member->st[1]->wMinute << ":"
					<< member->st[1]->wSecond << ":"
					<< member->st[1]->wMilliseconds
					<< " "
					<< member->st[2]->wMinute << ":"
					<< member->st[2]->wSecond << ":"
					<< member->st[2]->wMilliseconds
					<< "\n";
				fout.close();
				FORTH = false;
				FIRST = true;
				if (!ReleaseMutex(ghMutex))
				{
					cout << "ERROR write_log";
				}
				break;
			case WAIT_ABANDONED:
				return FALSE;
			}
		}
	}

	return TRUE;
}