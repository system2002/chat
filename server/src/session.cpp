#include "session.h"
#include "sessionManager.h"

namespace chat {

session::session(asio::io_context &context, sessionManager &managerRef):
    m_socket{context},
    m_readBuffer (1024),
    m_manager {managerRef}
{}

session::~session()
{
    std::cout << "session destroy" << std::endl;
}

void session::start()
{
    std::string str = "Hello! Welcom to server!";
    asyncRead();
    asyncSendData(asio::buffer(str));
}

void session::asyncRead()
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
            std::cerr << "Close client" << std::endl;
            closeSession();
        }
    });
}

void session::readHandler(const asio::error_code &error, std::size_t size)
{
    std::cout << "read: ";
    std::cout.write(m_readBuffer.data(), size) << std::endl;
    m_readBuffer.reserve(size);
    m_manager.sendNotMe(shared_from_this(), asio::buffer(m_readBuffer, size));
}

void session::closeSession()
{
    auto self = shared_from_this();
    m_manager.erase(shared_from_this());
    m_manager.printCount();
}
}
