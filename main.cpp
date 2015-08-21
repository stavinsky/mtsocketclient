#include <iostream>
#include "windows.h"
#include <string>
#include "clogger/logger.h"

typedef void(*Tmtconnect)( const wchar_t*,  const wchar_t *);
typedef int(*Tget_data)(wchar_t * );
typedef int(*Tsend_data)(const wchar_t *);
typedef void(*Tmtdisconnect)();

int main()
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
        std::cout << "functions ready"<<std::endl;


        mtconnect(L"127.0.0.1", L"9999");
        wchar_t buffer[1024];
        int res;
        while(true)
        {
            res = get_data(buffer);
            if(0 == res)
                if(-1 == send_data(buffer))
                    break;
            if (-1 == res)
                break;

            Sleep(10);
        }
        std::cout << "mtdisconnect" << std::endl;
        mtdisconnect();

    }


    return 0;
}
 


 
