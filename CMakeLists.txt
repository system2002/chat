cmake_minimum_required(VERSION 3.5)

project(asioChat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(server)
add_subdirectory(client)




