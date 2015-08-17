cmake_minimum_required (VERSION 2.6)
SET(CMAKE_TOOLCHAIN_FILE mingw.txt)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++  -static -O3 -s -Wall")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -O3 -s -Wall")

set(_REQUIRED_INCLUDES Winsock2.h)
set(_REQUIRED_LIBRARIES WS2_32.lib WSock32.lib)
set(CMAKE_REQUIRED_INCLUDES ${_REQUIRED_INCLUDES})
set(CMAKE_REQUIRED_LIBRARIES ${_REQUIRED_LIBRARIES})

find_package (Threads)


add_library(safequeue STATIC safequeue.cpp )
target_compile_features(safequeue PRIVATE cxx_range_for)


add_library(client STATIC client.cpp )
target_link_libraries(client ws2_32)
target_compile_features(client PRIVATE cxx_range_for)




add_library(mtsocket MODULE mtsocket.cpp)
target_link_libraries(mtsocket client ws2_32 ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(mtsocket PRIVATE cxx_range_for )


add_executable(main main.cpp)
target_link_libraries(main )





#set_property(TARGET main PROPERTY CXX_STANDARD 11)
#set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

#set_property(TARGET client PROPERTY CXX_STANDARD 11)
#set_property(TARGET client PROPERTY CXX_STANDARD_REQUIRED ON)

#set_property(TARGET safequeue PROPERTY CXX_STANDARD 11)
#set_property(TARGET safequeue PROPERTY CXX_STANDARD_REQUIRED ON)

#set_property(TARGET mtsocket PROPERTY CXX_STANDARD 11)
#set_property(TARGET mtsocket PROPERTY CXX_STANDARD_REQUIRED ON)
