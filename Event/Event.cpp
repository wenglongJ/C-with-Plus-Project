// Event.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
using namespace std;

DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

int tickets = 100;
HANDLE g_hEvent;

CRITICAL_SECTION g_cs;
int main()
{
	HANDLE hThread1;
	HANDLE hThread2;

	//g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	//CloseHandle(g_hEvent);

	InitializeCriticalSection(&g_cs);
	
	Sleep(4000);
	DeleteCriticalSection(&g_cs);
    return 0;
}

DWORD WINAPI Fun1Proc(LPVOID lpParameter) {
	char buf[100] = { 0 };
	while (TRUE) {
		//WaitForSingleObject(g_hEvent, INFINITE);
		EnterCriticalSection(&g_cs);
		if (tickets > 0) {
			sprintf_s(buf, "thread1 sell ticket : %d\n", tickets);
			cout << buf;
			tickets--;
			//SetEvent(g_hEvent);
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			//SetEvent(g_hEvent);
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}

DWORD WINAPI Fun2Proc(LPVOID lpParameter) {
	char buf[100] = { 0 };
	while (TRUE) {
		//WaitForSingleObject(g_hEvent, INFINITE);
		EnterCriticalSection(&g_cs);
		if (tickets > 0) {
			sprintf_s(buf, "thread2 sell ticket : %d\n", tickets);
			cout << buf;
			tickets--;
			//SetEvent(g_hEvent);
			LeaveCriticalSection(&g_cs);
		}
		else {
			//SetEvent(g_hEvent);
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}

