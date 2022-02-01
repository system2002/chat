#pragma once

#include <iostream>
#include <asio.hpp>
#include "sessionManager.h"


namespace chat {

class server_pimpl
{
public:
    server_pimpl(asio::io_context & context, asio::ip::tcp::endpoint ep);
private:
    asio::io_context & m_context;
    asio::ip::tcp::acceptor m_acceptor;
    void handleAccept(const asio::error_code& error, pSession newSession);
    void startAccept();
    sessionManager m_manager;
};
} //namespace chat
