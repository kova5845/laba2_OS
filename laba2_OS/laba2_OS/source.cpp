#include <iostream>
#include <vector>
#include "sourse.h"
#include <fstream>
#include <Windows.h>
#include <ctime>

using namespace std;
extern HANDLE ghEvent[EVENTCOUNT];


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
		dwWaitResult = WaitForSingleObject(ghEvent[0], INFINITE);
		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:

				member->table->setX(x);
				member->table->setY(x);
				GetLocalTime(member->st[0]);
				//cout << x << "  " << x << "  " << member->st[0]->wSecond << endl;
				cout << member->st[0]->wMinute << ":"
					<< member->st[0]->wSecond << ":"
					<< member->st[0]->wMilliseconds << " \n";
				x += h;
				ResetEvent(ghEvent[0]);
				SetEvent(ghEvent[1]);
				SetEvent(ghEvent[2]);
				break;
			default:
				cout << "ERROR 0";
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
		dwWaitResult = WaitForSingleObject(ghEvent[1], INFINITE);
		switch (dwWaitResult)
		{

			case WAIT_OBJECT_0:
				fout.open("file.txt", ios_base::app);
				fout << member->table->getX() << " " << member->table->getY() << "\n";
				GetLocalTime(member->st[1]);
				fout.close();
				/*cout << member->st[1]->wMinute << ":"
					<< member->st[1]->wSecond << ":"
					<< member->st[1]->wMilliseconds << "  ";*/
				ResetEvent(ghEvent[1]);
				if (!WaitForSingleObject(ghEvent[2], 0))
				{
					SetEvent(ghEvent[3]);
					
				}
				break;
			default:
				cout << "ERROR 1";
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
		dwWaitResult = WaitForSingleObject(ghEvent[2], INFINITE);
		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
				member->point->setX(member->table->getX());
				member->point->setX(member->table->getY());
				GetLocalTime(member->st[2]);
				/*cout << member->st[2]->wMinute << ":"
					<< member->st[2]->wSecond << ":"
					<< member->st[2]->wMilliseconds << "  ";*/
				ResetEvent(ghEvent[2]);
				if (!WaitForSingleObject(ghEvent[1], 0))
				{
					SetEvent(ghEvent[3]);
					
				}
				break;
			default:
				cout << "ERROR 2";
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
		dwWaitResult = WaitForSingleObject(ghEvent[3], INFINITE);
		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
				fout.open("file.log", ios_base::app);
				fout << member->table->getX() << " "
					<< member->st[0]->wMinute << ":"
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
				ResetEvent(ghEvent[3]);
				SetEvent(ghEvent[0]);
				break;
			default:
				cout << "ERROR 3";
		}
	}
	return TRUE;
}