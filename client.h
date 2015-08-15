#ifndef CLIENT_H
#define CLIENT_H
#define PORT 9999
#define DATA_BUFSIZE 5
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <queue>
#include <string>
#include "safequeue.cpp"
#include <thread>

class Client
{
public:
    Client(const char* addr, const char* port);
	~Client();
	void loop();
	void error(const char * msg);

    void handle_read();
    void write_handle();
    int do_read();
    int do_write();
    void do_close();
    int handle_close();
    void thread_loop();

	SOCKET client_socket;
    char read_buffer[DATA_BUFSIZE];
	WSADATA wsaData;
	WSANETWORKEVENTS hProcessEvent;
    int status;
    SafeQueue<std::string> send_queue;
    SafeQueue<std::string> recv_queue;
};

#endif
