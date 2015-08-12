#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "client.h"
#include <thread>


 
int main(int argc, char **argv)
{
    Client client("127.0.0.1", "9999");
    std::thread t(client.loop());
    std::cout << "test" << std::endl;

    return 0;
}
 


 
