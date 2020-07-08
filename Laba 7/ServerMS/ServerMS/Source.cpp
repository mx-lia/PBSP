#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

int main() {

	char bufwrite[50] = {}, bufread[50] = {};
	DWORD dw;
	bool b = false;
	clock_t t1, t2;
	HANDLE MAIL;


	MAIL = CreateMailslot("\\\\.\\mailslot\\slot", 300, 180000, NULL);
	
	while (true) 
	{
		ReadFile(MAIL, bufread, sizeof(bufread), &dw, NULL);
		if (!b) { t1 = clock(); b = true; }

		cout << bufread << endl;
		if (dw == 0)
			cout << "Error" << endl;

		if (strcmp(bufread, " ") == 0) 
		{ 
			t2 = clock(); 
			b = false; 
			cout << "Time:" << t2 - t1 << endl;;
		}
	}
	CloseHandle(MAIL);
	system("pause");
	return 0;
}