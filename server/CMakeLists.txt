add_library(serverLib
    include/chat/server.h

    src/server_impl.h
    src/sessionManager.h
    src/session.h
    src/server_impl.cpp
    src/sessionManager.cpp
    src/session.cpp
    src/server.cpp
    )

if (WIN32)
    target_link_libraries(serverLib ws2_32 wsock32)
endif()

if (UNIX)
    target_link_libraries(serverLib PUBLIC pthread)
endif()
target_include_directories(serverLib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

add_executable(server main.cpp)
target_link_libraries(server serverLib)

