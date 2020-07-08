#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

int main() {
	
	HANDLE MAIL;
	char bufwrite[50] = "Hello!!!!", bufread[50] = {};
	DWORD dw;
	int count = 0, i = 0;
	clock_t t1, t2;

	cout << "Size: ";
	cin >> count;


	cout << endl;

	MAIL = CreateFile("\\\\*\\mailslot\\slot", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	t1 = clock();
	while (i < count) 
	{
		_itoa_s(i, bufwrite, 10);
		
		i++;
		
		WriteFile(MAIL, bufwrite, strlen(bufwrite) + 1, &dw, NULL);

		if (dw == 0)
			cout << "Error" << endl;
		
	}
	t2 = clock();
	WriteFile(MAIL, " ", strlen(" ")+1, &dw, NULL);

	cout << "Time " << t2 - t1 << endl;
	CloseHandle(MAIL);
	system("pause");
	return 0;
}