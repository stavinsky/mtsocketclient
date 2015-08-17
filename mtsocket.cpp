#include "mtsocket.h"


MtSocket *client = NULL;



void mtconnect(const char* addr, const char* port)
{
    
    client = new MtSocket(addr, port);

    client->send_queue.enqueue("buffer");
    client->thread_loop();
//    delete client;
}


int get_data(char * buffer)
{
//    if(!client->recv_queue.empty())
//    {
//        strcpy(buffer, client->recv_queue.dequeue().c_str());
//        return 0;
//    }
//    else
//        return 1;
}

int send_data(const char * buffer)
{
//    client->send_queue.enqueue(buffer);
//    return 0;
}

void mtdisconnect()
{
    delete client;
}


