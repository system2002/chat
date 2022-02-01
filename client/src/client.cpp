#include <iostream>
#include "chat/client.h"
#include <cassert>
namespace {
    constexpr size_t read_buffer_size = 1024;
}


namespace chat {
client::client(asio::io_context &context, asio::ip::tcp::endpoint ep, CollbackRead_t &&collbackRead):
    m_context {context},
    m_socket{context},
    m_isConnected {false},
    m_readBuffer (read_buffer_size),
    m_collbackRead {std::move(collbackRead)}
{
    assert(m_collbackRead && "Empty callback on read");
    m_socket.async_connect(ep, [this](const asio::error_code &ec)
    {
        if (!ec)
        {
            std::cout << "Connect Ok" << std::endl;
            m_isConnected = true;
            asyncRead();
        }
        else
        {
            std::cerr << "Connect error: " << ec.message() << std::endl;
            m_context.stop();
            m_isConnected = false;
        }
    });

}

void client::asyncRead()
{
    m_socket.async_read_some(asio::buffer(m_readBuffer), [&](const asio::error_code& error, std::size_t size)
    {
        if (!error)
        {
            m_collbackRead(m_readBuffer.begin(), m_readBuffer.begin() + size);
            asyncRead();
        }
        else
        {
            std::cerr << "Server close\n";

            m_context.stop();
            m_isConnected = false;
        }
    });
}
}
