#include "Windows.h"
#include <iostream>

int main()
{
	auto const slot_name = TEXT("\\\\.\\mailslot\\Box");
	const auto mailslot = CreateMailslot(slot_name, 300,
		180000, nullptr);
	DWORD rb;
	char read_buffer[100];
	std::cout << "Wait for a client...";
	if (!ReadFile(mailslot, read_buffer, sizeof read_buffer, &rb, nullptr))
	{
		std::cout << "Read error\n";
		return 0;
	}
	std::cout << "Get message from client: " << std::endl << read_buffer << std::endl;
	CloseHandle(mailslot);
	system("pause");
	return 0;
}
