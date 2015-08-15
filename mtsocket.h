#ifndef MTSOCKET_H
#define MTSOCKET_H
#include "client.h"

extern "C" void mtconnect(const char* addr, const char* port);
extern "C" int get_data(char* buffer);
extern "C" int send_data(const char* buffer);
extern "C" void mtdisconnect();

class MtSocket: public Client
{
public:
    MtSocket(const char* addr, const char* port):Client(addr, port)
    {

    }

};


#endif // MTSOCKET_H
