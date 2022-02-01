#include <iostream>
#include <asio.hpp>
#include <thread>
#include <atomic>
#include <chrono>
#include "chat/client.h"

int main()
{
    chat::client::CollbackRead_t onReadData = [](chat::buffer_t::const_iterator lit, chat::buffer_t::const_iterator rit) -> void
    {
        std::cout <<"> ";
        std::cout << std::string(lit, rit);
        std::cout << std::endl;
    };

    std::atomic_bool stop = false;

    asio::io_context context;
    asio::ip::tcp::endpoint ep{asio::ip::address_v4::loopback(), 10000};
    std::cout << ep.address().to_string() << ":" << ep.port() << std::endl;
    asio::signal_set signal(context, SIGINT, SIGTERM);
    signal.async_wait([&context](const asio::error_code & err, int signal)
        {
            context.stop();
        });
    chat::client cl {context, ep, std::move(onReadData)};

    auto res = std::async(std::launch::async, [&context, &stop]()
    {
        context.run();
        stop = true;
    });

    while ((!stop))
    {
        std::string text;
        std::cin >> text;
        if (!cl.isConnected()) break;
        cl.asyncSendData(text);
    }
    std::cout << "Exit" << std::endl;
    return 0;
}
