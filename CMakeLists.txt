cmake_minimum_required (VERSION 2.6)
SET(CMAKE_TOOLCHAIN_FILE mingw.txt)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++  -static -O3 -s -Wall -Wextra -pedantic ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -O3 -s -Wall -Wextra -pedantic ")


set(CMAKE_REQUIRED_INCLUDES ${_REQUIRED_INCLUDES})
set(CMAKE_REQUIRED_LIBRARIES ${_REQUIRED_LIBRARIES})

find_package (Threads)



include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(socket_client)
add_subdirectory(clogger)
add_subdirectory(safequeue)

add_library(mtsocket MODULE mtsocket.cpp)
target_link_libraries(mtsocket client ws2_32 ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(mtsocket PRIVATE cxx_range_for )


add_executable(main main.cpp)
target_link_libraries(main )
target_compile_features(main PRIVATE cxx_range_for)

