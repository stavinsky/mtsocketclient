#include "client.h"

void Client::error(const char * msg = "")
{
	printf("WSA failed with error %d\n", WSAGetLastError());
	
}
Client::Client(const char* addr, const char* port)
{
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    
	int iResult;
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
        {
            error();
            return ;
        }
    else
            printf("WSAStartup() is OK!\n");
	
	ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
	
    iResult = getaddrinfo(addr, port, &hints, &result);
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) 
	{
       client_socket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (client_socket == INVALID_SOCKET) {
            error();
            WSACleanup();
            return ;
        }
        iResult = connect( client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (client_socket == INVALID_SOCKET) 
	{
        error();
        WSACleanup();
        return ;
    }
    
    ::WSAEventSelect(client_socket, event, FD_WRITE | FD_READ | FD_CLOSE);
    
}


void Client::loop()
{
	while(TRUE){
		DWORD ret;
		WSANETWORKEVENTS NetworkEvents;
		ret = WSAWaitForMultipleEvents(1, &event, FALSE, WSA_INFINITE, FALSE);
		if(ret == 0)
		{
			::WSAEnumNetworkEvents(client_socket,   &hProcessEvent, &NetworkEvents);
			if( (NetworkEvents.lNetworkEvents & FD_ACCEPT) && 
				(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0) )
				{
					std::cout<<"read"<<std::endl;
				}
		}
		
	}
}


