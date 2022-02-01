#include "server_impl.h"
#include "session.h"

namespace chat {

server_pimpl::server_pimpl(asio::io_context &context, asio::ip::tcp::endpoint ep):
    m_context {context},
    m_acceptor {context, ep},
    m_manager(context)
{
    startAccept();
}

void server_pimpl::handleAccept(const asio::error_code &error, pSession newSession)
{
    if (!error)
    {

        m_manager.insert(newSession);
        std::cout << "Accepted! client count: " << m_manager.count() << std::endl;
        newSession->start();
    }
    else
    {
        std::cout << "Accept error: " << error.value() << std::endl;
    }
    startAccept();
}

void server_pimpl::startAccept()
{
    pSession newSession = m_manager.newSession();
    m_acceptor.async_accept(newSession->socket(), [this, newSession](const asio::error_code &error)
    {
        handleAccept(error, newSession);
    });
}

}
