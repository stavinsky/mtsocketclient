#include <iostream>
#include "windows.h"



int main(int argc, char **argv)
{
    HINSTANCE dllHandle = NULL;
    dllHandle = LoadLibrary("libmtsocket.dll");
    if (NULL != dllHandle)
    {
        std::cout << "loaded"<<std::endl;
        typedef int(*pfunc)(const char*, const char*);
        pfunc  mtconnect;
        mtconnect = (pfunc)GetProcAddress(dllHandle,"mtconnect");
        mtconnect("127.0.0.1", "9999");

    }


    return 0;
}
 


 
