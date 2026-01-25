cmake_minimum_required(VERSION 3.23)

project(Networking_Demo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/enet-1.3.18)

add_executable(Networking_Demo)

target_sources(Networking_Demo
  PRIVATE
    src/server.cpp
)

target_include_directories(Networking_Demo
  PRIVATE
    thirdparty/enet-1.3.18/include
)

target_link_libraries(Networking_Demo
  PRIVATE
    enet
)