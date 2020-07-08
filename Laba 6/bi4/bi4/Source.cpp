#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	HANDLE hpipe;
	DWORD dw = 0;
	char bufwrite[50] = "abc";
	char bufread[50] = "abc";
	int kaka = 0, loop = 1000, i = 0;
	bool b;
	try {
		if ((hpipe = CreateFile("\\\\.\\DJorj\\pipe\\Tube", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw GetLastError();

		/*cout << "Enter loop " << endl;
		cin >> loop;*/

		while (i<loop) {
			_itoa_s(i, bufwrite, 10);

			b = TransactNamedPipe(hpipe, bufwrite, strlen(bufwrite) + 1, bufread, sizeof(bufread), &dw, NULL);

			cout << bufread << endl;
			i++;
		}
		//WriteFile(hpipe, "stop", strlen("stop") + 1, &dw, NULL);
	}
	catch (string msg)
	{
		cout << endl << msg;
	}

	CloseHandle(hpipe);
	system("pause");
	return 0;
}



