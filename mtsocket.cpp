#include "mtsocket.h"


MtSocket *client = NULL;



void mtconnect(const char* addr, const char* port)
{
    
    client = new MtSocket(addr, port);


    client->threaded_loop();
}


int get_data(char * buffer)
{
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
    client->put(buffer);
    return 0;
}

void mtdisconnect()
{
    delete client;
}


