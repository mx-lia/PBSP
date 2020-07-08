#include "Windows.h"
#include <iostream>

int main()
{
	DWORD wb;
	auto const slot_name = TEXT("\\\\DESKTOP-5EOQT1V\\mailslot\\Box");
	auto const write_buffer = "Hello from Mailslot";
	const auto mailslot_handler = CreateFile(slot_name, GENERIC_WRITE, FILE_SHARE_READ,
		nullptr, OPEN_EXISTING, NULL, nullptr);
	if (!WriteFile(mailslot_handler, write_buffer, strlen(write_buffer), &wb, nullptr))
	{
		std::cout << "Write error.";
		return 0;
	}
	std::cout << "Information wrote.\n";
	CloseHandle(mailslot_handler);
	system("pause");
	return 0;
}