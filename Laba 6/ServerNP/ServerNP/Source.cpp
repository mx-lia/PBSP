#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;

int main() {
	HANDLE hpipe;
	DWORD dw = 0;
	char buf[50] = {};
	char buf1[50] = {};
	bool b;
	int kaka = 0;
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\Tube");
	try {
		if ((hpipe = CreateNamedPipe(lpszPipename, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1 , 0, 0, NMPWAIT_WAIT_FOREVER, NULL)) == INVALID_HANDLE_VALUE)
			throw GetLastError();
		
		while (1) {
			ConnectNamedPipe(hpipe, NULL);
			while (1) {
				
				ReadFile(hpipe, buf, sizeof(buf), &dw, NULL);
				if (strcmp(buf, "stop") == 0)
					break;
				if (strcmp(buf, "qwe") == 0) {
					cout << "Message from CalledNamedPipe " << endl;
					break;
				}
				cout << buf << endl;
				kaka = atoi(buf) + 1;
				_itoa_s(kaka, buf, 10);
				WriteFile(hpipe, buf, strlen(buf) + 1, &dw, NULL);
			}
			DisconnectNamedPipe(hpipe);
		}

	}
	catch (string Msg)
	{
		cout << endl << Msg;
	}



	cout << "Done" << endl;
	DisconnectNamedPipe(hpipe);
	system("pause");
	return 0;
}