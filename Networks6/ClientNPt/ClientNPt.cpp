// ClientNP.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <Winsock2.h>
#define PIPE TEXT("\\\\.\\pipe\\Tube")
#define MAX_SIZE_OF_BUFFER 64
int main()
{
	HANDLE hPipe;
	//DWORD dwWritten;
	DWORD bytes;
	char buffer[] = "Hello Pipe";
	char* outbuffer = new char[MAX_SIZE_OF_BUFFER];
	memset(outbuffer, NULL, MAX_SIZE_OF_BUFFER);
	try
	{
		hPipe = CreateFile(PIPE,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
			throw "Please, check server!";
		DWORD state = PIPE_READMODE_MESSAGE;
		SetNamedPipeHandleState(hPipe, &state, NULL, NULL);
		TransactNamedPipe(hPipe, buffer, sizeof(buffer), outbuffer, MAX_SIZE_OF_BUFFER, &bytes, NULL);
		//outbuffer[bytes] = 0x00;
		puts(outbuffer);
		CloseHandle(hPipe);
	}
	catch (char* err)
	{
		puts(err);
	}
	delete[] outbuffer;
	system("pause");
	return (0);
}
