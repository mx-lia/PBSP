// ClientNP.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Winsock2.h>
#define MAX_SIZE_OF_BUFFER 64
#define PIPE TEXT("\\\\.\\pipe\\Tube") //DESKTOP-HED0J8B(Olesya), DESKTOP-L93MRGU(Ksusha), Alina, DESKTOP-O75SA5J(Yulya), DESKTOP-EE6S0A9(Nikita), DESKTOP-HPU1E1O(Vadim)

int main()
{
	HANDLE hPipe;
	DWORD dwWritten;
	char* buffer = new char[MAX_SIZE_OF_BUFFER];
	memset(buffer, NULL, MAX_SIZE_OF_BUFFER);
	try
	{
		hPipe = CreateFile(PIPE,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
			throw("Please, check server!");
		WriteFile(hPipe,
			"Hello Pipe",
			12,   // = length of string + terminating '\0' !!!
			&dwWritten,
			NULL);
		ReadFile(hPipe, buffer, MAX_SIZE_OF_BUFFER, &dwWritten, NULL);
		printf("Get from server: %s\n", buffer);
		CloseHandle(hPipe);
	}
	catch (char* err)
	{
		puts(err);
	}
	system("pause");
	return (0);
}
