add_library(clientLib STATIC
    include/chat/client.h
    src/client.cpp)

if (WIN32)
    target_link_libraries(clientLib ws2_32)
endif()

if (UNIX)
    target_link_libraries(clientLib PUBLIC pthread)
endif()

target_include_directories(clientLib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)


add_executable(client main.cpp)
target_link_libraries(client clientLib)


