#include "client.h"

Client::Client(const char* addr, const char* port)
{
	struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
	int iResult;
	result = WSAStartup(MAKEWORD(2,2), &wsaData)
    if (iResult != 0)
        {
            error();
            return 1;
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
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) 
	{
        error();
        WSACleanup();
        return ;
    }
    
    
    
}

void Client::error(const char * msg = "")
{
	printf("WSA failed with error %d\n", WSAGetLastError());
	
}
void Client::loop()
{
	while(FALSE){
		
	}
}


BOOL CreateSocketInformation(SOCKET s)
{
            LPSOCKET_INFORMATION SI;
 
            if ((EventArray[EventTotal] = WSACreateEvent()) == WSA_INVALID_EVENT)
            {
                        printf("WSACreateEvent() failed with error %d\n", WSAGetLastError());
                        return FALSE;
            }
            else
                        printf("WSACreateEvent() is OK!\n");
 
            if ((SI = (LPSOCKET_INFORMATION) GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
            {
                        printf("GlobalAlloc() failed with error %d\n", GetLastError());
                        return FALSE;
            }
            else
                        printf("GlobalAlloc() for LPSOCKET_INFORMATION is OK!\n");
 
            // Prepare SocketInfo structure for use
            SI->Socket = s;
            SI->BytesSEND = 0;
            SI->BytesRECV = 0;
 
            SocketArray[EventTotal] = SI;
            EventTotal++;
            return(TRUE);
}

void FreeSocketInformation(DWORD Event)
{
            LPSOCKET_INFORMATION SI = SocketArray[Event];
            DWORD i;
 
            closesocket(SI->Socket);
            GlobalFree(SI);
 
            if(WSACloseEvent(EventArray[Event]) == TRUE)
                        printf("WSACloseEvent() is OK!\n\n");
            else
                        printf("WSACloseEvent() failed miserably!\n\n");
 
            // Squash the socket and event arrays
            for (i = Event; i < EventTotal; i++)
            {
                        EventArray[i] = EventArray[i + 1];
                        SocketArray[i] = SocketArray[i + 1];
            }
            EventTotal--;
}
