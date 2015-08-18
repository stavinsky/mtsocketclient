#include "client.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <thread>
void Client::error()
{
    printf("WSA failed with error %d\n", WSAGetLastError());
    status = 1;
}

Client::Client(const char* addr, const char* port)
{
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    status = 0;
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

void Client::do_read()
{
    int bytes_received=0;
    bytes_received = recv(client_socket, read_buffer, sizeof(read_buffer), 0);
    if(bytes_received > 0)
    {
        std::string tmp(read_buffer, bytes_received);
        recv_queue.enqueue(tmp);
        handle_read();
    }
}

void Client::do_write()
{
    if (send_queue.empty())
        return;
    int ret=0;
    const char *buffer = send_queue.dequeue().c_str();
    ret=send(client_socket, buffer,  strlen(buffer),0);
    if(ret == SOCKET_ERROR)
        error();
    handle_write();
    return;
}
void Client::handle_read()
{

}
void Client::handle_write()
{

}

void Client::threaded_loop(void)
{
    std::thread t(&Client::loop, this);
    t.join();
}

void Client::loop()
{
    WSAEVENT event = WSA_INVALID_EVENT;
    event = WSACreateEvent();
    bool can_write=false;
    unsigned int ret;
    ::WSAEventSelect(client_socket, event, FD_WRITE | FD_READ | FD_CLOSE);
    while(true)
    {

        if(status!=0)
            break;

        if(can_write == true )
            do_write();

        WSANETWORKEVENTS NetworkEvents;

        ret = WSAWaitForMultipleEvents(1, &event, FALSE, 5, FALSE);
        if( ret == WSA_WAIT_FAILED )
        {
            error();
            break;
        }

        ::WSAEnumNetworkEvents(client_socket,   event, &NetworkEvents);

        if( (NetworkEvents.lNetworkEvents & FD_READ) &&
            (NetworkEvents.iErrorCode[FD_READ_BIT] == 0) )
        {
            do_read();
        }
        if(( NetworkEvents.lNetworkEvents & FD_CLOSE ) || NetworkEvents.iErrorCode[FD_CLOSE_BIT !=0 ])
        {
            do_close();
        }
        if((NetworkEvents.lNetworkEvents & FD_WRITE) &&
                (NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0))
        {

            can_write = true;
        }



	}
}

void Client::put(std::string string)
{
    send_queue.enqueue(string);
}

std::string Client::get()
{
    return recv_queue.dequeue();
}
bool Client::empty()
/*
 * return true if recv_queue is empry
 *
 */
{
return recv_queue.empty();
}
void Client::do_close()
{
    closesocket(client_socket);
    status=1;
    WSACleanup();
}

Client::~Client()
{

}

