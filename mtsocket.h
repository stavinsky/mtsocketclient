#ifndef MTSOCKET_H
#define MTSOCKET_H
#include "socket_client/client.h"

extern "C" __declspec(dllexport) void mtconnect(const wchar_t *, const wchar_t *);
extern "C" __declspec(dllexport) int get_data(wchar_t *);
extern "C" __declspec(dllexport) int send_data(const wchar_t *);
extern "C" __declspec(dllexport) void mtdisconnect();

class MtSocket: public Client
{
public:
    MtSocket(const char* addr, const char* port):Client(addr, port)
    {

    }

};


#endif // MTSOCKET_H
