#pragma once
#include <asio.hpp>
#include <set>
#include <memory>
#include <iostream>
#include "sessionManager.h"

class server
{
public:
    server(asio::io_context & context, asio::ip::tcp::endpoint ep);
private:
    //asio::ip::tcp::socket m_socket;
    asio::io_context & m_context;
    asio::ip::tcp::acceptor m_acceptor;
    void handleAccept(const asio::error_code& error, pSession newSession);
    void startAccept();
    sessionManager m_manager;
};
