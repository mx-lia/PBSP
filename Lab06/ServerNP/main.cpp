#include "windows.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "ServerNP" << endl;

    try {
        HANDLE h_NP;

        char rbuf[50];
        DWORD rb = sizeof(rbuf);

        if ((h_NP = CreateNamedPipe(R"(\\.\pipe\Tube)", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, NULL,
                                    NULL, INFINITE, NULL)) == INVALID_HANDLE_VALUE)
            throw "Error: CreateNamedPipe";

        while (true) {
            if (!ConnectNamedPipe(h_NP, NULL))
                throw "Error: ConnectNamedPipe";
            while (true) {

                if (!ReadFile(h_NP, rbuf, sizeof(rbuf), &rb, NULL))
                    if (GetLastError() == ERROR_BROKEN_PIPE) {
                        cout << "The write handle has been closed" << endl;
                        break;
                    } else {
                        throw "Error: ReadFile";
                    }

                cout << rbuf << endl;

                if (!WriteFile(h_NP, rbuf, sizeof(rbuf), &rb, NULL))
                    throw "Error: WriteFile";
            }
            if (!DisconnectNamedPipe(h_NP))
                throw "Error: DisconnectNamedPipe";
        }
        if (!CloseHandle(h_NP))
            throw "Error: CloseHandle";
    }
    catch (char const *e) {
        cout << e << endl;
    }
    catch (string e) {
        cout << e << endl;
    }
    catch (...) {
        cout << "Error" << endl;
    }

    return 0;
}