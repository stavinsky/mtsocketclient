#include "mtsocket.h"
#include <thread>

MtSocket *client = NULL;
std::thread *t = NULL;


void mtconnect(const char* addr, const char* port)
{
    if(client or t)
        return;
    client = new MtSocket(addr, port);
    t = new std::thread(&client->loop, client);
    //t.join();


}


int get_data(char * buffer)
{
    if(1 == client->status)
    {
        return -1;
    }
    if(!client->empty())
    {
        strcpy(buffer, client->get().c_str());
        return 0;
    }
    else
        return 1;

}

int send_data(const char * buffer)
{
    if(1 == client->status)
    {
        return -1;
    }
    client->put(buffer);
    return 0;
}

void mtdisconnect()
{
    if(client)
        delete client;
    if(t)
        delete t;
}


