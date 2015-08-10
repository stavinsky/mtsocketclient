#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "client.h"
#define PORT 9999
#define DATA_BUFSIZE 8192
 

 
int main(int argc, char **argv)
{
            SOCKET Listen;
            SOCKET Accept;
            SOCKADDR_IN InternetAddr;
            LPSOCKET_INFORMATION SocketInfo;
            DWORD Event;
            WSANETWORKEVENTS NetworkEvents;
            WSADATA wsaData;
            DWORD Flags;
            DWORD RecvBytes;
            DWORD SendBytes;
  std::cout << "test1" << std::endl;

  return 0;
}
 


 
