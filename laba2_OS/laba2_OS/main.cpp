#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include "sourse.h"
#include <process.h>
#include <ctime>



using namespace std;

DWORD WINAPI SecondThread(PVOID pvParam);

int main()
{
	Table* table = new Table;
	Point* point = new Point;
	SYSTEMTIME** st = new SYSTEMTIME* [3];
	for (int i = 0; i < 3; i++)
		st[i] = new SYSTEMTIME;
	Member* member = new Member(table, point, st);
	DWORD dwThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) count_func, member,
		0, &dwThreadID);
	Sleep(1000);
	CloseHandle(hThread);
	return 0;
}

DWORD WINAPI SecondThread(PVOID pvParam) {

	*((int*)pvParam) = 5;
	
	return (0);
}