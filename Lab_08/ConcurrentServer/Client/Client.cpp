#include "stdafx.h"

using namespace std;

bool SystemMessage(char *ch)
{
	bool result = false;
	char Timeout[50] = "Close: timeout;",
		 Close[50] = "Close: finish;",
		 Abort[50] = "Close: Abort;";
	
	if (strcmp(ch, Timeout) == NULL)
		result = true;
	else if (strcmp(ch, Abort) == NULL)
		result = true;
	else if (strcmp(ch, Close) == NULL)
		result = true;

	return result;
}

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

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}

bool GetServer(char* call, SOCKADDR_IN* from, int* flen, SOCKET * cC, SOCKADDR_IN * all)
{
	char ibuf[50],
		 obuf[50];
	int libuf = 0,
		lobuf = 0;

	if ((lobuf = sendto(*cC, call, strlen(call) + 1, NULL, (sockaddr*)all, sizeof(*all))) == SOCKET_ERROR)
		throw SetErrorMsgText("Sendto: ", WSAGetLastError());

	if ((libuf = recvfrom(*cC, ibuf, sizeof(ibuf), NULL, (sockaddr*)from, flen)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			return false;
		else
			throw SetErrorMsgText("Recv: ", WSAGetLastError());
		
		if (strcmp(call, ibuf) == 0)
			return true;
		else
			return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_CTYPE, "Russian");
	SetConsoleTitle("Client");

	int port = 0;
	SOCKET ClientSocket;
	WSADATA wsaData;

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		
		if ((ClientSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());

		int ch = 0;
		bool fin = false;
		int cCall = 0;
		int max = 100,
			lobuf = 1;
		char obuf[50] = "";
		char ibuf[50] = "";
		int bport = 2000;

		char Call[50];
		//char Error[50] = "ErrorInquiry";
		char Name[50] = "server";
		char Calls[50] = "KelErnBor";

		SOCKADDR_IN Server = { 0 };
		Server.sin_family = AF_INET;
		Server.sin_port = htons(port);

		SOCKADDR_IN Server_IN;
		int Flen = sizeof(Server);
		int chs = 0;
		
		cout << "[1] ������� ��� �������" << endl << "[2] ��������" << endl << "--> ";
		cin >> chs;
		
		if (chs == 1)
		{
			cout << "��� �������: ";
			cin  >> Name;
			hostent* s = gethostbyname(Name);
		
			if (s == NULL)
				throw "������ �� ������;";
			
			cout << "������� ���� �������: ";
			cin  >> port;
			
			Server_IN.sin_addr = *(struct in_addr *)s->h_addr_list[0];
		}
		else if (chs == 2)
		{
			cout << "������� ��������: ";
			cin  >> Calls;

			SOCKET cC;

			if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
				throw SetErrorMsgText("Socket: ", WSAGetLastError());

			int optval = 1;
			if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
				throw SetErrorMsgText("SetSockOpt: ", WSAGetLastError());
			
			struct timeval timeout;
			timeout.tv_sec = 3;
			timeout.tv_usec = 0;
			if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
				throw SetErrorMsgText("SetSockOpt: ", WSAGetLastError());

			SOCKADDR_IN all;
			all.sin_family = AF_INET;
			all.sin_port = htons(bport);
			all.sin_addr.s_addr = INADDR_BROADCAST;
			
			SOCKADDR_IN clnt;
			memset(&clnt, 0, sizeof(clnt));
			int lc = sizeof(clnt);

			bool bsr = GetServer(Calls, &clnt, &lc, &cC, &all);
			
			if (bsr == false)
				throw "������ �� ������;";
			else
			{
				Server_IN.sin_addr.s_addr = clnt.sin_addr.s_addr;
				
				if (closesocket(cC) == SOCKET_ERROR)
					throw SetErrorMsgText("Closesocket: ", WSAGetLastError());
				
				cout << "������� ���� �������: ";
				cin  >> port;
			}

		}
		else
			throw "�� ����������� ����� ��� �������";

		Server_IN.sin_family = AF_INET;
		Server_IN.sin_port = htons(port);

		if ((connect(ClientSocket, (sockaddr*)&Server_IN, sizeof(Server_IN))) == SOCKET_ERROR)
			throw "������ �����������;";

		while (!fin)
		{
			cout << "Service: " << endl << "[1] Rand" << endl << "[2] Time" << endl << "[3] Echo" << endl << "--> ";
			cin  >> cCall;

			if (cCall == 1 || cCall == 2 || cCall == 3)
			{
				fin = true;
				break;
			}

			else
			{
				if (closesocket(ClientSocket) == SOCKET_ERROR)
					throw SetErrorMsgText("Closesocket: ", WSAGetLastError());
				
				throw "�� ����������� ����� ��� �������;";
			}
		}

		switch (cCall)
		{
			case 1:	strcpy(Call, "Rand");
					cout << "Enter Rand command or other:" << endl;
					break;
			case 2: strcpy(Call, "Time");
					cout << "Enter Time command or other:" << endl;
					break;
			case 3:	strcpy(Call, "Echo");
					cout << "Enter string or exit :" << endl;
					break;
			default: strcpy(Call, "Echo");
		}

		if ((lobuf = send(ClientSocket, Call, sizeof(Call), NULL)) == SOCKET_ERROR)
			throw SetErrorMsgText("Send: ", WSAGetLastError());
		
		char rCall[50];
		if ((lobuf = recv(ClientSocket, rCall, sizeof(rCall), NULL)) == SOCKET_ERROR)
			throw SetErrorMsgText("Recv: ", WSAGetLastError());

		if (strcmp(Call, rCall) != 0)
			throw "������ �������";
		else
		{
			bool Check = true;
			fin = false;

			u_long nonblk = 1;
			
			if (SOCKET_ERROR == ioctlsocket(ClientSocket, FIONBIO, &nonblk))
				throw SetErrorMsgText("Ioctlsocket: ", WSAGetLastError());
			
			clock_t StartTime = clock();
			bool rcv = true;

			char iib[50];
			cout << "-->";
			cin  >> iib;

			while (!fin)
			{
				if (rcv)
				{
					if ((lobuf = send(ClientSocket, iib, sizeof(iib), NULL)) == SOCKET_ERROR)
						throw "Error;";
					
					rcv = false;
				}

				if ((recv(ClientSocket, obuf, sizeof(obuf), NULL)) == SOCKET_ERROR)
				{
					switch (WSAGetLastError())
					{
						case WSAEWOULDBLOCK: Sleep(100); break;
						default: throw SetErrorMsgText("Recv: ", WSAGetLastError());
					}
				}
				else
				{
					if (SystemMessage(obuf))
					{
						printf("������ ��������� �����������: %s\n", obuf);
						break;
					}
					else
						printf("������� ���������: [%s]\n", obuf);

					rcv = true;
				}
			}

			clock_t FinishTime = clock();
			printf("Time: %lf sec.\n", (double)(FinishTime - StartTime) / CLOCKS_PER_SEC);
		}

		if (closesocket(ClientSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("Closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (char* errorMsgText)
	{
		cout << errorMsgText << endl;
	}

	system("pause");
	return 0;
}