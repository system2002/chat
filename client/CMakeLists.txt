add_library(clientLib STATIC
    include/chat/client.h
    src/client.cpp)

target_link_libraries(clientLib ASIO::ASIO)
target_include_directories(clientLib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

add_executable(client main.cpp)
target_link_libraries(client clientLib)


