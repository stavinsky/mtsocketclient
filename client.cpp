#include "client.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Winerror.h>
#include <stdio.h>
#include <thread>


void Client::error()
{
    int error_number = WSAGetLastError();
    char windows_error_text[100];
    char message[1024];
    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,                 // It´s a system error
                         NULL,                                      // No string to be formatted needed
                         error_number,                               // Hey Windows: Please explain this error!
                         MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),  // Do it in the standard language
                         windows_error_text,              // Put the message here
                         99,                     // Number of bytes to store the message
                         NULL);

    snprintf(message, sizeof(message), "%d - %s", error_number, windows_error_text);
    logger.log(message);
    status = 1;
}

Client::Client(const char* addr, const char* port):
    logger("logfile.txt")
{

    status = 0;
    logger.log("constructor");
    if (0 != WSAStartup(MAKEWORD(2,2), &wsaData))
    {
        error();
        return ;
    }
    logger.log("wsa started");
    if(0 != do_connect(addr, port))
    {
        error();
        return;
    }



}

int Client::do_connect(const char* addr, const char * port)
{   char message[1024];
    snprintf(message, sizeof(message), "connect to %s:%s", addr, port);
    logger.log(message);
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if(0 != getaddrinfo(addr, port, &hints, &result))
    {
        return -1;
    }

    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next)
    {
        client_socket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (INVALID_SOCKET == client_socket)
            return -1;


        if (SOCKET_ERROR == connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen))
        {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (INVALID_SOCKET == client_socket )
    {
        return -1;
    }
    logger.log("connected");
    return 0;
}



void Client::do_read()
{
    int bytes_received=0;
    bytes_received = recv(client_socket, read_buffer, DATA_BUFSIZE, 0);
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
    char buffer[DATA_BUFSIZE];
    strcpy(buffer, send_queue.dequeue().c_str());
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
            do_close();
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
