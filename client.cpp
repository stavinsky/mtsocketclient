#include "client.h"

void Client::error(const char * msg = "")
{
    printf("WSA failed with error%s %d\n", msg, WSAGetLastError());
    err = 1;
	
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
            error();
            continue;
        }
        break;
    }
//    freeaddrinfo(result);
//    if (client_socket == INVALID_SOCKET)
//    {
//        error();
//        WSACleanup();
//        return ;
//    }

    
}


void Client::loop()
{
    WSAEVENT event = WSA_INVALID_EVENT;
    event = WSACreateEvent();
    WSANETWORKEVENTS NetworkEvents;
    ::WSAEventSelect(client_socket, event, FD_WRITE | FD_READ | FD_CLOSE);
    std::cout << "connected"  <<std::endl;
    while(TRUE)
    {
        if(err!=0)
            break;
		DWORD ret;

        ret = WSAWaitForMultipleEvents(0, &event, FALSE, WSA_INFINITE, FALSE);
        if((ret == WSA_WAIT_FAILED) || (ret == WSA_WAIT_TIMEOUT))
        {
            continue;
        }
        if(ret >= 0)
        {
            ::WSAEnumNetworkEvents(client_socket,   event, &NetworkEvents);

            if( (NetworkEvents.lNetworkEvents & FD_READ) &&
				(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0) )
				{
					std::cout<<"read"<<std::endl;
				}
            if((NetworkEvents.lNetworkEvents & FD_CLOSE))
                {

                    error("close");
                }

        }

	}
}
Client::~Client()
{
    std::cout << "destructor" << std::endl;
}

void hello(void)
{
	std::cout << " hello world" << std::endl;
}
