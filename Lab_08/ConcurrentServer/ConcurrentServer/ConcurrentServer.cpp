#include "stdafx.h"
#include "Global.h"
#include "AcceptServer.h"
#include "DispathServer.h"
#include "GarbageCleaner.h"
#include "ConsolePipe.h"
#include "ResponseServer.h"

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_CTYPE, "Russian");
	srand((unsigned)time(NULL));
	SetConsoleTitle("Concurrent Server");
	
	cout << "ConcurrentServer �������:\n" << endl;

	if (argc > 1)
	{
		int tmp = atoi(argv[1]);
		if (tmp >= 0 && tmp <= 65535)
		{
			port = atoi(argv[1]);
			cout << "������������ TCP-����: " << port << ";" << endl;
		}
		else
		{
			cout << "Wrong TCP-port;" << endl;
		}
	}
	else
	{
		cout << "������������ TCP-����: " << port << " (default);" << endl;
	}

	if (argc > 2)
	{
		int tmp = atoi(argv[2]);
		if (tmp >= 0 && tmp <= 65535)
		{
			uport = atoi(argv[2]);
			cout << "������������ UDP-����: " << uport << ";" << endl;
		}
		else
		{
			cout << "Wrong UDP-port;" << endl;
		}
	}
	else
	{
		cout << "������������ UDP-����: " << uport << " (default);" << endl;
	}

	if (argc > 3)
	{
		dllname = argv[3];
	}

	if (argc > 4)
	{
		npname = argv[4];
		cout << "CallNamedPipe: " << npname << ";" << endl;
	}
	else
	{
		cout << "CallNamedPipe: " << npname << " (default);" << endl;
	}

	if (argc > 5)
	{
		ucall = argv[5];
		cout << "��������: " << ucall << ";" << endl;
	}
	else
	{
		cout << "��������: " << ucall << " (default);" << endl;
	}

	volatile TalkersCmd cmd = Start;

	InitializeCriticalSection(&scListContact);

	st1 = LoadLibrary(dllname);
	ts1 = (HANDLE(*)(char*, LPVOID))GetProcAddress(st1, "SSS");
	
	if (st1 == NULL)
		cout << "Fail DLL;" << endl;
	else
		cout << "��������� DLL-����������: " << dllname << ";" << endl << endl;

	hAcceptServer = CreateThread(NULL, NULL, AcceptServer, (LPVOID)&cmd, NULL, NULL);
	HANDLE hDispathServer = CreateThread(NULL, NULL, DispathServer, (LPVOID)&cmd, NULL, NULL);
	HANDLE hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner, (LPVOID)&cmd, NULL, NULL);
	HANDLE hConsolePipe = CreateThread(NULL, NULL, ConsolePipe, (LPVOID)&cmd, NULL, NULL);
	HANDLE hResponseServer = CreateThread(NULL, NULL, ResponseServer, (LPVOID)&cmd, NULL, NULL);

	SetThreadPriority(hGarbageCleaner, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hDispathServer, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hConsolePipe, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hResponseServer, THREAD_PRIORITY_ABOVE_NORMAL);
	SetThreadPriority(hAcceptServer, THREAD_PRIORITY_HIGHEST);


	WaitForSingleObject(hAcceptServer, INFINITE);
	WaitForSingleObject(hDispathServer, INFINITE);
	WaitForSingleObject(hGarbageCleaner, INFINITE);
	WaitForSingleObject(hConsolePipe, INFINITE);
	WaitForSingleObject(hResponseServer, INFINITE);

	CloseHandle(hAcceptServer);
	CloseHandle(hDispathServer);
	CloseHandle(hGarbageCleaner);
	CloseHandle(hConsolePipe);
	CloseHandle(hResponseServer);

	DeleteCriticalSection(&scListContact);

	FreeLibrary(st1);

	system("pause");
	return 0;
}