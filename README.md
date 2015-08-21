# mtsocketclient
test c++ library using to send data from MT4 Terminal to some socket server. 

This is a test project. Here you can find how to use winapi to write pure socket application on windows. 
Also you can find sample of using std::thread, non-blocking sockets. 
Project compiles on windows, but I used OS X to develop, so I made cross compilation. 
You can use this code as you want and if you found some bugs or can suggest some improvements - welcome

## dependencies
All dependencies added by git submodules
https://github.com/stavinsky/clogger
https://github.com/stavinsky/socket_client
https://github.com/stavinsky/safe_queue




Compilation:

```
OS X:

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=mingw.txt ../
make
```

MSYS2:

```
mkdir build
cd build
cmake -G"MSYS Makefiles" ../
make
```


