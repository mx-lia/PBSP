#include "windows.h"
#include <string>
#include "string.h"
#include <iostream>

#define STOP_WORD "~"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "ClientNP" << endl << endl;

    try {
        HANDLE h_NP;

        char rbuf[50];
        char wbuf[50] = "Hello from client ";
        DWORD rb = sizeof(rbuf);
        DWORD wb = sizeof(wbuf);

        if ((h_NP = CreateFile(R"(\\.\pipe\Tube)", GENERIC_WRITE | GENERIC_READ,
                               FILE_SHARE_WRITE | FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
            throw "Error: CreateFile";

        int numberOfMessages;

        cout << "Please enter the number of messages " << endl;
        cin >> numberOfMessages;

        for (int i = 0; i < numberOfMessages; i++) {

            char inum[6];
            sprintf(inum, "%d", i + 1);
            char buf[sizeof(wbuf) + sizeof(inum)];
            strcpy(buf, wbuf);
            strcat(buf, inum);
            wb = sizeof(wbuf);

            if (!WriteFile(h_NP, buf, sizeof(wbuf), &wb, NULL))
                throw "Error: WriteFile";
            if (!ReadFile(h_NP, rbuf, sizeof(rbuf), &rb, NULL))
                throw "Error: ReadFile";

            cout << rbuf << endl;
        }

        CloseHandle(h_NP);
    }
    catch (char const *e) {
        cout << e << endl;
    } catch (const std::exception &ex) {
        cout << "Error" << endl;
    }

    return 0;
}