#define PORT 9999
#define DATA_BUFSIZE 5
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>

extern "C" void hello(void);

class Client
{
public:
    Client(const char* addr, const char* port);
	~Client();
	void loop();
	void error(const char * msg);

    int handle_read(char * buffer);
    int write_handle();
    int do_read();
    int do_write();
    void do_close();
    int handle_close();

	SOCKET client_socket;
    char read_buffer[DATA_BUFSIZE];
	WSADATA wsaData;
	WSANETWORKEVENTS hProcessEvent;
    int status;
    std::queue<std::string> msg_queue;
};

