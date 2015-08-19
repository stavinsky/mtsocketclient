#include "mtsocket.h"
#include <thread>
#include <stdlib.h>
#include <stdio.h>
MtSocket *client = NULL;
std::thread *t = NULL;


void mtconnect(const wchar_t * addr, const wchar_t * port)
{
    std::cout << "mtconnect"<<std::endl;
    if(client || t)
        return;
    std::wstring ws_addr=addr;
    std::wstring ws_port=port;
    std::string st_addr(ws_addr.begin(), ws_addr.end());
    std::string st_port(ws_port.begin(), ws_port.end());
    client = new MtSocket(st_addr.c_str(), st_port.c_str());
    t = new std::thread(&client->loop, client);



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

int send_data(const wchar_t * wcharmsg)
{
    if(1 == client->status)
    {
        return -1;
    }
    std::wstring wmsg = wcharmsg;
    std::string stmsg(wmsg.begin(), wmsg.end());
    client->put(stmsg);
    return 0;
}

void mtdisconnect()
{
    client->status = 1;
    client->do_close();

    t->join();
    if(NULL != client)
    {
        delete client;
        client = NULL;
    }
    if(NULL != t)
    {
        delete t;
        t = NULL;
    }
}


