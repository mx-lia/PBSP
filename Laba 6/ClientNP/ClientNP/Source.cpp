#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

int main() 
{
	HANDLE hpipe;
	DWORD dw = 0;
	char buf[50] = {};
	int kaka = 0, loop = 0,i=0;
	try {
		if ((hpipe = CreateFile("\\\\DJorj\\pipe\\Tube", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING,NULL,NULL)) == INVALID_HANDLE_VALUE)
			throw GetLastError();
		cout << "Enter loop " << endl;
		cin >> loop;

		while (i<loop) {
			_itoa_s(i, buf, 10);
			WriteFile(hpipe, buf, strlen(buf)+1, &dw, NULL);
			ReadFile(hpipe, buf, sizeof(buf), &dw, NULL);
			cout << buf << endl;
			i++;
		}
		WriteFile(hpipe, "stop", strlen("stop") + 1, &dw, NULL);
	}
	catch(string msg)
	{
		cout << endl << msg;
	}
	
	CloseHandle(hpipe);
	system("pause");
	return 0;
}