#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	HANDLE hpipe;
	DWORD dw = 0,dwmode;
	char bufwrite[50] = {};
	char bufread[50] = {};
	int kaka = 0, loop = 0, i = 0;
	long lo = 0;
	bool b;
	try {
		WaitNamedPipe("\\\\DJorj\\pipe\\Tube", 5000);
		if ((hpipe = CreateFile("\\\\DJorj\\pipe\\Tube", GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)


			

		dwmode = PIPE_READMODE_MESSAGE;
		SetNamedPipeHandleState(hpipe, &dwmode, NULL, NULL);

		cout << "Enter loop " << endl;
		cin >> loop;

		while (i<loop) {
			_itoa_s(i, bufwrite, 10);

			
			b = TransactNamedPipe(hpipe, bufwrite, strlen(bufwrite) + 1, bufread, sizeof(bufread), &dw, NULL);
		
			cout << bufread << endl;
			i++;
		}
		WriteFile(hpipe, "stop", strlen("stop") + 1, &dw, NULL);
	}
	catch (string msg)
	{
		cout << endl << msg;
	}
	
	CloseHandle(hpipe);
	system("pause");
	return 0;
	}
	

	
