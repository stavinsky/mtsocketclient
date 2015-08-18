#ifndef CLIENT_H
#define CLIENT_H
#define DATA_BUFSIZE 1024

#include <string>
#include "safequeue.cpp"
#include <winsock2.h>

class Client
{
public:
    Client(const char* addr, const char* port);
    ~Client();
	void loop();
    void threaded_loop();

    void handle_read();
    void handle_write();
    void handle_close();

    std::string get();
    void put(std::string string);
    bool empty();


private:

    void do_read();
    void do_write();
    void do_close();
    void error();
    SafeQueue<std::string> send_queue;
    SafeQueue<std::string> recv_queue;
    int status;

    SOCKET client_socket;
    char read_buffer[DATA_BUFSIZE];
    WSADATA wsaData;
    WSANETWORKEVENTS hProcessEvent;
};

#endif
