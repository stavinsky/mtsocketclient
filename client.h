#define PORT 9999
#define DATA_BUFSIZE 8192
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>

extern "C" void hello(void);

class Client
{
public:
    Client(const char* addr, const char* port);
	~Client();
	void loop();
	void error(const char * msg);
	SOCKET client_socket;

	WSADATA wsaData;
	WSANETWORKEVENTS hProcessEvent;
    int err = 0;
};

 

typedef struct _SOCKET_INFORMATION {
   CHAR Buffer[DATA_BUFSIZE];
   WSABUF DataBuf;
   SOCKET Socket;
   DWORD BytesSEND;
   DWORD BytesRECV;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;
