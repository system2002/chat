#pragma once
#include <iostream>
#include <vector>
#include <asio.hpp>


namespace chat {
using buffer_t = std::vector<char>;

class client
{
public:
    using CollbackRead_t = std::function<void(buffer_t::const_iterator, buffer_t::const_iterator)>;
    client(asio::io_context & context, asio::ip::tcp::endpoint ep, CollbackRead_t &&collbackRead);
    bool isConnected() const { return m_isConnected; }

    void asyncSendData(const std::string &text)
    {
        asyncSendData(asio::buffer(text));
    }

    template<typename Buffer_t>
    void asyncSendData(const Buffer_t &buffer)
    {
        m_socket.async_write_some(buffer, [&](const asio::error_code& error, std::size_t size)
        {
            if (error)
            {
                std::cerr << "Send error: " << error.value();
                m_context.stop();
                m_isConnected = false;
            }
        });
    }

private:
    asio::io_context & m_context;
    asio::ip::tcp::socket m_socket;
    bool m_isConnected;
    std::vector<char> m_readBuffer;
    const CollbackRead_t m_collbackRead;
    void asyncRead();
};

} // nmespace chat
