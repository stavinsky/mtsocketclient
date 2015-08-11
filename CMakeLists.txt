cmake_minimum_required (VERSION 2.6)

SET(CMAKE_TOOLCHAIN_FILE mingw.txt)


add_library(client STATIC client.cpp )
target_link_libraries( client ws2_32 )
add_executable(main main.cpp)

SET(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -O3 -s")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-static-libgcc -static-libstdc++ -static -O3 -s")
target_link_libraries(main client )
