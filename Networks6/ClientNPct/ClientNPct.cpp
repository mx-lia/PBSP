
#include "stdafx.h"
#include <Winsock2.h>
#define PIPE TEXT("\\\\.\\pipe\\Tube")
#define MAX_SIZE_OF_BUFFER 64
int main()
{
	DWORD bytes;
	char buffer[] = "Hello Pipe";
	char* outbuffer = new char[MAX_SIZE_OF_BUFFER];
	memset(outbuffer, NULL, MAX_SIZE_OF_BUFFER);
	try
	{
		DWORD state = PIPE_READMODE_MESSAGE;
		CallNamedPipe(PIPE, buffer, sizeof(buffer), outbuffer, MAX_SIZE_OF_BUFFER, &bytes, NMPWAIT_WAIT_FOREVER);
		puts(outbuffer);
	}
	catch (char* err)
	{
		puts(err);
	}
	delete[] outbuffer;
	system("pause");
	return (0);
}
