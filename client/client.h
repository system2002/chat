#pragma once
#include <iostream>
#include <vector>
#include <asio.hpp>

using buffer_t = std::vector<char>;

class client
{
public:
    client(asio::io_context & context, asio::ip::tcp::endpoint ep);
    bool isConnected() const { return m_isConnected; }

    template<typename Buffer_t>
    void asyncSendData(const Buffer_t &buffer)
    {
        m_socket.async_write_some(buffer, [&](const asio::error_code& error, std::size_t size)
        {
            if (error)
            {
                std::cerr << "send error: " << error.value();
            }
        });
    }

private:
    asio::io_context & m_context;
    asio::ip::tcp::socket m_socket;
    bool m_isConnected;
    std::vector<char> m_readBuffer;

    void asyncRead();
    void readHandler(const asio::error_code& error, std::size_t size);

};

