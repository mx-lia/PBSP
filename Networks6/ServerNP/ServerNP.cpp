#include "stdafx.h"
#include <Winsock2.h>
#include <string>
constexpr auto pipe = TEXT("\\\\.\\pipe\\Tube");
constexpr auto max_size_of_buffer = 64;

int main()
{
	try
	{
		while (true) {
			DWORD dw_read;
			const auto buffer = new char[max_size_of_buffer];
			const auto h_pipe = CreateNamedPipe(pipe,
				PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
				1,
				1024 * 16,
				1024 * 16,
				NMPWAIT_USE_DEFAULT_WAIT,
				nullptr);
			if (h_pipe == INVALID_HANDLE_VALUE)
				throw "Named Pipe doesn't create";
			if (!ConnectNamedPipe(h_pipe, nullptr))
				throw "Troubles with client connection";
			while (ReadFile(h_pipe, buffer, strlen(buffer) - 1, &dw_read, nullptr) != FALSE)
			{
				buffer[dw_read] = '\0';
				puts(buffer);
				WriteFile(h_pipe, buffer, strlen(buffer), &dw_read, nullptr);
			}

			DisconnectNamedPipe(h_pipe);
			CloseHandle(h_pipe);
			delete[] buffer;
		}
	}
	catch (char* err)
	{
		puts(err);
	}
	system("pause");
	return 0;
}