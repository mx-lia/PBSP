#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>

#define THREE_MINUTES 3 * 60000

using namespace std;

int main() {
    setlocale(0, "");

    HANDLE sH;
    DWORD rb;
    char buf[26];

    try {
        if ((sH = CreateMailslot(R"(\\.\mailslot\Box)",
                                 500, THREE_MINUTES, NULL)) == INVALID_HANDLE_VALUE) {
            throw "CreateMailslot exception " + to_string(GetLastError());
        }
        while (true) {
            if (!ReadFile(sH, buf, sizeof(buf), &rb, NULL)) {
                int lastError = GetLastError();
                if (lastError == ERROR_SEM_TIMEOUT) {
                    throw "3 minutes timeout finished";
                } else {
                    throw "ReadFile exception " + to_string(GetLastError());
                }
            }
            cout << buf << endl;
        }
        CloseHandle(sH);
    }
    catch (char const* errorMessage) {
        cout << errorMessage << endl;
    }
}