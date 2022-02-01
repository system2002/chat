#include <iostream>
#include <future>
#include "chat/server.h"

void signal_handler(asio::io_context &context, const asio::error_code &, int)
{
    std::cout << "Server stop" << std::endl;
    context.stop();
}


int main()
{
    asio::io_context context;
    asio::ip::tcp::endpoint ep{asio::ip::address_v4::loopback(), 10000};
    std::cout << ep.address().to_string() << ":" << ep.port() << std::endl;
    chat::server srv {context, ep};
    asio::signal_set signal(context, SIGINT, SIGTERM);
    signal.async_wait([&context](const asio::error_code & err, int signal)
        {
            signal_handler(context, err, signal);
        });
    std::future<void> future = std::async(std::launch::async, [&]()
    {
        context.run();
    });
    future.wait();
    return 0;
}
