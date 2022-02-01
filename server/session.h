#pragma once
#include <asio.hpp>
#include <iostream>

class sessionManager;

class session: public std::enable_shared_from_this<session>
{
public:
    session (asio::io_context & context, sessionManager & managerRef):
        m_socket{context},
        m_readBuffer (1024),
        m_manager {managerRef}
    {}

    void start()
    {
        char text[] = "hello!";
        asyncRead();
        asyncSendData(asio::buffer(text, sizeof (text)));
    }

    template<typename Buffer_t>
    void asyncSendData(const Buffer_t &buffer)
    {
        m_socket.async_write_some(buffer, [&](const asio::error_code& error, std::size_t size)
        {
            if (error)
            {
                std::cerr << "send error: " << error.value() << std::endl;
            }
        });
    }
    void asyncRead()
    {
        m_socket.async_read_some(asio::buffer(m_readBuffer), [&](const asio::error_code& error, std::size_t size)
        {
            if (!error)
            {
                readHandler(error, size);
                asyncRead();
            }
            else
            {
                std::cerr << "read error: " << error.value() << std::endl;
                closeSession();
            }
        });
    }
    void readHandler(const asio::error_code& error, std::size_t size)
    {
        std::cout << "read: ";
        std::cout.write(m_readBuffer.data(), size);
    }

    asio::ip::tcp::socket &socket()
    {
        return m_socket;
    }

private:
    asio::ip::tcp::socket m_socket;
    std::vector<char> m_readBuffer;
    sessionManager & m_manager;
    void closeSession();
};

