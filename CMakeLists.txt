cmake_minimum_required (VERSION 2.6)

SET(CMAKE_TOOLCHAIN_FILE mingw.txt)
set(_REQUIRED_INCLUDES Winsock2.h)
set(_REQUIRED_LIBRARIES WS2_32.lib WSock32.lib)
set(CMAKE_REQUIRED_INCLUDES ${_REQUIRED_INCLUDES})
set(CMAKE_REQUIRED_LIBRARIES ${_REQUIRED_LIBRARIES})
find_package (Threads)
add_library(client STATIC client.cpp )
add_library(safequeue STATIC safequeue.cpp)
target_compile_features(safequeue PRIVATE cxx_range_for)

target_link_libraries( client ws2_32)
add_executable(main main.cpp)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set_property(TARGET main PROPERTY CXX_STANDARD 11)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++  -O3 -s")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-static-libgcc -static-libstdc++ -static -O3 -s")
target_compile_features(client PRIVATE cxx_range_for)


target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT} client  )
