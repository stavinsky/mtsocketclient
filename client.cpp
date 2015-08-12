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
    err = 0;
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
//
//        return ;
//    }

    
}
int Client::do_read()
{
    int bytes_received=0;
    bytes_received = recv(client_socket, read_buffer, sizeof(read_buffer), 0);
    if(bytes_received > 0)
    {
        char result[bytes_received];
        memset(result, 0, bytes_received);
        strncpy(result, read_buffer, bytes_received);
        result[bytes_received]='\0';

        handle_read(result);
    }
}

int Client::do_write()
{
    std::cout << "write" << std::endl;
}
int Client::handle_read(char *buffer)
{
    std::cout<<buffer<<std::endl;
    return 0;
}
int Client::write_handle()
{

}

void Client::loop()
{
    WSAEVENT event = WSA_INVALID_EVENT;
    event = WSACreateEvent();
    std::cout << "connected"  <<std::endl;
    ::WSAEventSelect(client_socket, event, FD_WRITE | FD_READ | FD_CLOSE);
    while(TRUE)
    {

        //std::cout << count++ << std::endl;
        if(err!=0)
            do_close();
		DWORD ret;

        WSANETWORKEVENTS NetworkEvents;

        ret = WSAWaitForMultipleEvents(1, &event, FALSE, WSA_INFINITE, FALSE);
        if((ret == WSA_WAIT_FAILED) || (ret == WSA_WAIT_TIMEOUT))
        {
            continue;
        }
        if(ret >= 0)
        {
            ::WSAEnumNetworkEvents(client_socket,   event, &NetworkEvents);

            if( (NetworkEvents.lNetworkEvents & FD_READ) &&
                (NetworkEvents.iErrorCode[FD_READ_BIT] == 0) )
            {
                do_read();
            }
            if( NetworkEvents.lNetworkEvents & FD_CLOSE )
            {
                do_close();
            }
            if((NetworkEvents.lNetworkEvents & FD_WRITE) &&
                    (NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0))
            {
                do_write();
            }


        }

	}
}
void Client::do_close()
{
    WSACleanup();
}

Client::~Client()
{

}

void hello(void)
{
	std::cout << " hello world" << std::endl;
}
