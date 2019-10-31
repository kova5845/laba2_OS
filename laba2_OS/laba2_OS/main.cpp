#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include "sourse.h"
#include <process.h>
#include <ctime>

using namespace std;

HANDLE ghEvent[EVENTCOUNT];

int main()
{
	Table* table = new Table;
	Point* point = new Point;
	SYSTEMTIME** st = new SYSTEMTIME* [3];
	for (int i = 0; i < 3; i++)
		st[i] = new SYSTEMTIME;
	Member* member = new Member(table, point, st);
	DWORD dwThreadID;
	for (int i = 0; i < EVENTCOUNT; i++)
	{
		ghEvent[i] = CreateEvent(NULL, TRUE, FALSE, TEXT("event" + i));
	}
	SetEvent(ghEvent[0]);

	HANDLE* hThread = new HANDLE[THREADCOUNT];
	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) count_func, member,
		0, &dwThreadID);
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)write_in_file, member,
		0, &dwThreadID);
	hThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)write_in_Point, member,
		0, &dwThreadID);
	hThread[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)write_log, member,
		0, &dwThreadID);


	WaitForMultipleObjects(THREADCOUNT, hThread, TRUE, INFINITE);

	
	for (int i = 0; i < THREADCOUNT; i++)
		CloseHandle(hThread[i]);
	for (int i = 0; i < EVENTCOUNT; i++)
		CloseHandle(ghEvent);
	
	
	return 0;
}
