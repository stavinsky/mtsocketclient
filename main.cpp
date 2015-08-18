#include <iostream>
#include "windows.h"
#include <string>

typedef void(*Tmtconnect)(const char*, const char *);
typedef int(*Tget_data)(char * );
typedef int(*Tsend_data)(const char *);
typedef void(*Tmtdisconnect)();

int main(int argc, char **argv)
{
    HINSTANCE dllHandle = NULL;
    dllHandle = LoadLibrary("libmtsocket.dll");
    if (NULL != dllHandle)
    {
        std::cout << "loaded"<<std::endl;

        Tmtconnect mtconnect;
        Tget_data get_data;
        Tsend_data send_data;
        Tmtdisconnect mtdisconnect;
        mtconnect = (Tmtconnect)GetProcAddress(dllHandle,"mtconnect");
        get_data = (Tget_data)GetProcAddress(dllHandle, "get_data");
        send_data= (Tsend_data)GetProcAddress(dllHandle, "send_data");
        mtdisconnect = (Tmtdisconnect)GetProcAddress(dllHandle, "mtdisconnect");


        mtconnect("127.0.0.1", "9999");
        char buffer[1024];
        int res;
        while(true)
        {
            res = get_data(buffer);
            if(0 == res)
                if(-1 == send_data(buffer))
                    break;
            else if (-1 == res)
                break;

            Sleep(10);
        }
        mtdisconnect();

    }


    return 0;
}
 


 
