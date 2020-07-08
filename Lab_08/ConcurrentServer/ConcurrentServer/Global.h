#pragma once
#include <iostream>
#include <string>
#include <list>
#include <time.h>
#include "locale.h"
#include "Winsock2.h"              
#pragma comment(lib,"WS2_32.lib")
#include "Windows.h"
#include "Error.h"

using std::string;
using std::list;
using namespace std;

int port = 2000;
int uport = 2000;
char* dllname = "ServiceLibrary";
char* npname = "smc";
char* ucall = "KEB";
int AS_SQUIRT = 10;

HANDLE (*ts1)(char*, LPVOID);
HANDLE hAcceptServer;
HMODULE st1;
HANDLE Event=CreateEvent(NULL, FALSE, FALSE, NULL);

enum TalkersCmd {Start, Stop, Exit, Statistics, Wait, Shutdown, Getcommand};

volatile LONG Accept=0;
volatile LONG Fail=0;
volatile LONG Finished=0;
volatile LONG Work=0;

CRITICAL_SECTION scListContact;

struct Contact    
{
	enum TE
	{                
		EMPTY,
		ACCEPT,
		CONTACT
	} type;

	enum ST
	{                 
		WORK,
		ABORT,
		TIMEOUT,
		FINISH
	} sthread;

	SOCKET s;
	SOCKADDR_IN prms;
	int lprms;
	HANDLE hthread;
	HANDLE htimer;

	bool TimerOff;
	bool CloseConn;

	char msg[50];
	char srvname[15];

	HANDLE hAcceptServer;

	Contact(TE t = EMPTY, char* namesrv = "")
	{
		memset(&prms, 0, sizeof(SOCKADDR_IN));  
		
		lprms = sizeof(SOCKADDR_IN);
		type = t;             
		
		strcpy(srvname, namesrv);  
		
		msg[0] = 0;
		CloseConn = false;
		TimerOff = false;
	};            

	void SetST(ST sth, char* m = "" ) 
	{
		sthread = sth;     
		strcpy(msg, m);
	}           
};

typedef list <Contact> ListContact;  
ListContact Contacts;

void CALLBACK ASWTimer(LPVOID Lprm, DWORD, DWORD) 
{   
	char obuf[50] = "Close: timeout;";
	Contact *client = (Contact*) Lprm;
	EnterCriticalSection(&scListContact);
	client->TimerOff = true;
	client->sthread  =Contact::TIMEOUT;
	LeaveCriticalSection(&scListContact);

	if((send(client->s, obuf, sizeof(obuf)+1, NULL)) == SOCKET_ERROR)
		throw SetErrorMsgText("Send: ", WSAGetLastError());

	SYSTEMTIME stt;
	GetLocalTime(&stt);
	
	printf("%d.%d.%d %d:%02d Timeout ", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute);
	cout << client->srvname << ";" << endl;
}

void CALLBACK ASStartMessage(DWORD Lprm)
{   
	Contact *client = (Contact*) Lprm;
	char* sn = client->srvname;
	
	SYSTEMTIME stt;
	GetLocalTime(&stt);
	
	printf("%d.%d.%d %d:%02d ", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute);
	cout << sn << " started;" << endl;
}

void CALLBACK ASFinishMessage(DWORD Lprm)
{   
	Contact *client = (Contact*) Lprm;
	
	char* sn = client->srvname;
	
	SYSTEMTIME stt;
	GetLocalTime(&stt);
	
	printf("%d.%d.%d %d:%02d ", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute);
	cout << sn << " stoped;" << endl;
}