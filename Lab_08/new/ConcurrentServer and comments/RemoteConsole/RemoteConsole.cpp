#include "Winsock2.h"                // ���������  WS2_32.dll
#pragma comment(lib, "WS2_32.lib")   // �������  WS2_32.dll
#include "stdafx.h"

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR:          msgText = "WSAEINTR";         break;
	case WSAEACCES:         msgText = "WSAEACCES";        break;
		//..........���� WSAGetLastError ..........................
	case		WSAEFAULT: msgText = "	��������� �����"; break;
	case		WSAEINVAL: msgText = "	������ � ���������"; break;
	case		WSAEMFILE: msgText = "	������� ����� ������ �������"; break;
	case		WSAEWOULDBLOCK: msgText = "	������ �������� ����������"; break;
	case		WSAEINPROGRESS: msgText = "	�������� � �������� ��������"; break;
	case		WSAEALREADY: msgText = "	�������� ��� �����������"; break;
	case		WSAENOTSOCK: msgText = "	����� ����� �����������"; break;
	case		WSAEDESTADDRREQ: msgText = "	��������� ����� ������������"; break;
	case		WSAEMSGSIZE: msgText = "	��������� ������� �������"; break;
	case		WSAEPROTOTYPE: msgText = "	������������ ��� ��������� ��� ������"; break;
	case		WSAENOPROTOOPT: msgText = "	������ � ����� ���������"; break;
	case		WSAEPROTONOSUPPORT: msgText = "	�������� �� ��������������"; break;
	case		WSAESOCKTNOSUPPORT: msgText = "	��� ������ �� ��������������"; break;
	case		WSAEOPNOTSUPP: msgText = "	�������� �� ��������������"; break;
	case		WSAEPFNOSUPPORT: msgText = "	��� ���������� �� ��������������"; break;
	case		WSAEAFNOSUPPORT: msgText = "	��� ������� �� �������������� ����������"; break;
	case		WSAEADDRINUSE: msgText = "	����� ��� ������������"; break;
	case	WSAEADDRNOTAVAIL: msgText = "		����������� ����� �� ����� ���� �����������"; break;
	case WSAENETDOWN: msgText = "		���� ���������"; break;
	case WSAENETUNREACH: msgText = "		���� �� ���������"; break;
	case WSAENETRESET: msgText = "		���� ��������� ����������"; break;
	case WSAECONNABORTED: msgText = "	����������� ����� �����"; break;
	case WSAECONNRESET: msgText = "		����� �������������"; break;
	case WSAENOBUFS: msgText = "		�� ������� ������ ��� �������"; break;
	case WSAEISCONN: msgText = "		����� ��� ���������"; break;
	case WSAENOTCONN: msgText = "		����� �� ���������"; break;
	case WSAESHUTDOWN: msgText = "		������ ��������� send : ����� �������� ������"; break;
	case WSAETIMEDOUT: msgText = "		���������� ���������� ��������  �������"; break;
	case WSAECONNREFUSED: msgText = "		���������� ���������"; break;
	case WSAEHOSTDOWN: msgText = "		���� � ����������������� ���������"; break;
	case WSAEHOSTUNREACH: msgText = "		��� �������� ��� �����"; break;
	case WSAEPROCLIM: msgText = "		������� ����� ���������"; break;
	case WSASYSNOTREADY: msgText = "		���� �� ��������"; break;
	case WSAVERNOTSUPPORTED: msgText = "		������ ������ ����������"; break;
	case WSANOTINITIALISED: msgText = "		�� ��������� ������������� WS2_32.DLL"; break;
	case WSAEDISCON: msgText = "		����������� ����������"; break;
	case WSATYPE_NOT_FOUND: msgText = "		����� �� ������"; break;
	case WSAHOST_NOT_FOUND: msgText = "		���� �� ������"; break;
	case WSATRY_AGAIN: msgText = "		������������������ ���� �� ������"; break;
	case WSANO_RECOVERY: msgText = "		��������������  ������"; break;
	case WSANO_DATA: msgText = "		��� ������ ������������ ����"; break;
	//case WSA_INVALID_HANDLE: msgText = "		��������� ���������� �������  � �������"; break;
	//case WSA_INVALID_PARAMETER: msgText = "		���� ��� ����� ���������� � �������"; break;
	//case WSA_IO_INCOMPLETE: msgText = "		������ ����� - ������ �� � ���������� ���������"; break;
	//case WSA_IO_PENDING: msgText = "		�������� ���������� �����"; break;
	//case WSA_NOT_ENOUGH_MEMORY: msgText = "		�� ���������� ������"; break;
	//case WSA_OPERATION_ABORTED: msgText = "		�������� ����������"; break;
	//case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default: msgText = "***ERROR***";
		break;
	};
	return msgText;
}
string SetPipeError(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	SetConsoleTitle("Remote Console"); // ��������� ����������� ����

	try
	{
		printf("\nCommands:\n 1 - Start  \t \n 2 - Stop  \t \n 3 - Exit  \t \n 4 - Statistics  \n 5 - Wait  \t\n 6 - Shutdown  \t \n 7 - Finish RConsole\n\n");
		char ReadBuf[50] = "";// ������ ��� ������� ��������� �� �������
		char WriteBuf[2] = "";// ������ ��� �������� ��������� �������
		DWORD nBytesRead;
		DWORD nBytesWrite;

		int Code = 0;// ��� �������

		char serverName[256];
		char PipeName[512];
		bool result;


		cout << "Enter server name: ";
		cin >> serverName;
		result = sprintf(PipeName, "\\\\%s\\pipe\\smc", serverName);


		BOOL fSuccess;

		SECURITY_ATTRIBUTES SecurityAttributes;
		SECURITY_DESCRIPTOR SecurityDescriptor;

		fSuccess = InitializeSecurityDescriptor(
			&SecurityDescriptor,
			SECURITY_DESCRIPTOR_REVISION);

		if (!fSuccess) {
			throw new string("InitializeSecurityDescriptor(): ������");
		}

		fSuccess = SetSecurityDescriptorDacl(
			&SecurityDescriptor,
			TRUE,
			NULL,
			FALSE);

		if (!fSuccess) {
			throw new string("SetSecurityDescriptorDacl(): ������");
		}

		SecurityAttributes.nLength = sizeof(SecurityAttributes);
		SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
		SecurityAttributes.bInheritHandle = FALSE;

		HANDLE hNamedPipe = CreateFile(PipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, &SecurityAttributes);

		do
		{
			printf("Command: ");
			scanf("%d", &Code);
			if (Code>0 && Code<7)
			{
				sprintf(WriteBuf, "%d", Code - 1);
				if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL))
					throw "WriteFile: ������ ";
				if (ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
					cout << ReadBuf << endl;
				else
					throw "ReadFile: ������ ";

			}
			else if (Code>7) printf("�������� �������.\n\n");
		} while (Code != 7 && Code != 3 && Code != 6);
	}
	catch (char* ErrorPipeText)
	{
		printf("%s", ErrorPipeText);
		cout << GetLastError() << endl;
	}
	system("pause");
	return 0;
}
