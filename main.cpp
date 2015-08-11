#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "client.h"
#define PORT 9999
#define DATA_BUFSIZE 8192


 
int main(int argc, char **argv)
{
    Client client("127.0.0.1", "9999");
    client.loop();
    std::cout << "test" << std::endl;

    return 0;
}
 


 
