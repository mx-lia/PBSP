#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <ctime>

using namespace std;

int main() {
    setlocale(0, "");

    HANDLE cH;
    char buf[26] = "Hello from Maislot-client";
    DWORD lBuf;

    try {
        if ((cH = CreateFile(R"(\\.\mailslot\Box)",
                             GENERIC_WRITE,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING,
                             NULL, NULL)) == INVALID_HANDLE_VALUE)
            throw "CreateFile exception";

        int count;
        cout << "Number of messages: ";
        cin >> count;

        clock_t start = clock();

        for (int i = 0; i < count; i++) {

            if (!WriteFile(cH, buf, sizeof(buf), &lBuf, NULL))
                throw "WriteFile exception";
        }
        printf("Time taken: %.2fs\n", (double) (clock() - start) / CLOCKS_PER_SEC);
        CloseHandle(cH);
    }
    catch (char const *errorMessage) {
        cout << errorMessage << endl;
    }
}