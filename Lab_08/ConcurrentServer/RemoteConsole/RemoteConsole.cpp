#include "stdafx.h"

string GetErrorMsgText (int code)
{
	string msgText;

	switch (code)
	{
		case WSAEINTR:				 msgText = "������ ������� ��������\n";						  break;
		case WSAEACCES:				 msgText = "���������� ����������\n";						  break;
		case WSAEFAULT:				 msgText = "��������� �����\n";								  break;
		case WSAEINVAL:				 msgText = "������ � ���������\n";							  break;
		case WSAEMFILE:				 msgText = "������� ����� ������ �������\n";				  break;
		case WSAEWOULDBLOCK:		 msgText = "������ �������� ����������\n";					  break;
		case WSAEINPROGRESS:		 msgText = "�������� � �������� ��������\n";				  break;
		case WSAEALREADY: 			 msgText = "�������� ��� �����������\n";					  break;
		case WSAENOTSOCK:   		 msgText = "����� ����� �����������\n";						  break;
		case WSAEDESTADDRREQ:		 msgText = "��������� ����� ������������\n";				  break;
		case WSAEMSGSIZE:  			 msgText = "��������� ������� �������\n";				      break;
		case WSAEPROTOTYPE:			 msgText = "������������ ��� ��������� ��� ������\n";		  break;
		case WSAENOPROTOOPT:		 msgText = "������ � ����� ���������\n";					  break;
		case WSAEPROTONOSUPPORT:	 msgText = "�������� �� ��������������\n";					  break;
		case WSAESOCKTNOSUPPORT:	 msgText = "��� ������ �� ��������������\n";				  break;
		case WSAEOPNOTSUPP:			 msgText = "�������� �� ��������������\n";					  break;
		case WSAEPFNOSUPPORT:		 msgText = "��� ���������� �� ��������������\n";			  break;
		case WSAEAFNOSUPPORT:		 msgText = "��� ������� �� �������������� ����������\n";	  break;
		case WSAEADDRINUSE:			 msgText = "����� ��� ������������\n";						  break;
		case WSAEADDRNOTAVAIL:		 msgText = "����������� ����� �� ����� ���� �����������\n";	  break;
		case WSAENETDOWN:			 msgText = "���� ���������\n";								  break;
		case WSAENETUNREACH:		 msgText = "���� �� ���������\n";							  break;
		case WSAENETRESET:			 msgText = "���� ��������� ����������\n";					  break;
		case WSAECONNABORTED:		 msgText = "����������� ����� �����\n";						  break;
		case WSAECONNRESET:			 msgText = "����� �������������\n";							  break;
		case WSAENOBUFS:			 msgText = "�� ������� ������ ��� �������\n";				  break;
		case WSAEISCONN:			 msgText = "����� ��� ���������\n";							  break;
		case WSAENOTCONN:			 msgText = "����� �� ���������\n";							  break;
		case WSAESHUTDOWN:			 msgText = "������ ��������� send: ����� �������� ������\n";  break;
		case WSAETIMEDOUT:			 msgText = "���������� ���������� ��������  �������\n";		  break;
		case WSAECONNREFUSED:		 msgText = "���������� ���������\n";						  break;
		case WSAEHOSTDOWN:			 msgText = "���� � ����������������� ���������\n";			  break;
		case WSAEHOSTUNREACH:		 msgText = "��� �������� ��� �����\n";						  break;
		case WSAEPROCLIM:			 msgText = "������� ����� ���������\n";						  break;
		case WSASYSNOTREADY:		 msgText = "���� �� ��������\n";							  break;
		case WSAVERNOTSUPPORTED:	 msgText = "������ ������ ����������\n";					  break;
		case WSANOTINITIALISED:		 msgText = "�� ��������� ������������� WS2_32.DLL\n";		  break;
		case WSAEDISCON:			 msgText = "����������� ����������\n";						  break;
		case WSATYPE_NOT_FOUND:		 msgText = "����� �� ������\n";								  break;
		case WSAHOST_NOT_FOUND:		 msgText = "���� �� ������\n";								  break;
		case WSATRY_AGAIN:			 msgText = "������������������ ���� �� ������\n";			  break;
		case WSANO_RECOVERY:		 msgText = "�������������� ������\n";						  break;
		case WSANO_DATA:			 msgText = "��� ������ ������������ ����\n";				  break;
		case WSAEINVALIDPROCTABLE:	 msgText = "��������� ������\n";							  break;
		case WSAEINVALIDPROVIDER:	 msgText = "������ � ������ �������\n";						  break;
		case WSAEPROVIDERFAILEDINIT: msgText = "���������� ���������������� ������\n";			  break;
		case WSASYSCALLFAILURE:		 msgText = "��������� ���������� ���������� ������\n";		  break;
		default:					 msgText = "Error\n";										  break;
	};

	return msgText;
}

string SetPipeError(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_CTYPE, "Russian");
	SetConsoleTitle("Remote Console");

	try
	{
		printf("��������:\n[1] ������ \t\n[2] ��������� \t\n[3] ����� \t\n[4] ���������� \n[5] �������� \t\n[6] ���������� \t\n[7] ����� �� RConsole\n\n");
		
		char ReadBuf[50] = "";
		char WriteBuf[10] = "";
		char serverName[256];
		char PipeName[512];

		int Code = 0;
		bool result;
		
		DWORD nBytesRead;
		DWORD nBytesWrite;
		
		cout << "������� ��� �������: ";
		cin  >> serverName;
		result = sprintf(PipeName, "\\\\%s\\pipe\\smc", serverName);


		BOOL fSuccess;

		SECURITY_ATTRIBUTES SecurityAttributes;
		SECURITY_DESCRIPTOR SecurityDescriptor;

		fSuccess = InitializeSecurityDescriptor(&SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);

		if (!fSuccess)
		{
			throw new string("InitializeSecurityDescriptor(): ������");
		}

		fSuccess = SetSecurityDescriptorDacl(&SecurityDescriptor, TRUE, NULL, FALSE);

		if (!fSuccess)
		{
			throw new string("SetSecurityDescriptorDacl(): ������");
		}

		SecurityAttributes.nLength = sizeof(SecurityAttributes);
		SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
		SecurityAttributes.bInheritHandle = FALSE;

		HANDLE hNamedPipe = CreateFile(PipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, &SecurityAttributes);

		do
		{
			printf("������� ��� ��������: ");
			scanf("%d", &Code);
			
			if (Code>0 && Code<7)
			{
				sprintf(WriteBuf, "%d", Code - 1);
				
				if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL))
					throw "WriteFile: ������ ";
				
				if (ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
					cout << ReadBuf << endl;
				else
					throw "ReadFile: ������";

			}
			else if (Code>7)
				printf("�������� �������.\n\n");
		}
		while (Code != 7 && Code != 3 && Code != 6);
	}
	catch (char* ErrorPipeText)
	{
		printf("%s", ErrorPipeText);
		cout << GetLastError() << endl;
	}

	system("pause");
	return 0;
}