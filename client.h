#define PORT 9999
#define DATA_BUFSIZE 8192
#include <winsock2.h>
#include <stdio.h>

class Client
{
	Client(const char* addr, const char* port);
	~Client();
	void loop();
	void error(const char * msg = "");
	SOCKET client_socket;
	WSAEVENT event;
	WSADATA wsaData;
	LPSOCKET_INFORMATION socket_information;
};

 

typedef struct _SOCKET_INFORMATION {
   CHAR Buffer[DATA_BUFSIZE];
   WSABUF DataBuf;
   SOCKET Socket;
   DWORD BytesSEND;
   DWORD BytesRECV;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;
