#ifndef MTSOCKET_H
#define MTSOCKET_H
#include "client.h"

extern "C" __declspec(dllexport) void mtconnect(const char* addr, const char* port);
extern "C" __declspec(dllexport) int get_data(char* buffer);
extern "C" __declspec(dllexport) int send_data(const char* buffer);
extern "C" __declspec(dllexport) void mtdisconnect();

class MtSocket: public Client
{
public:
    MtSocket(const char* addr, const char* port):Client(addr, port)
    {

    }

};


#endif // MTSOCKET_H
