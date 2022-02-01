#pragma once

#include <memory>
#include <asio.hpp>

namespace chat {

class server_pimpl;

class server
{
public:
    server(asio::io_context & context, asio::ip::tcp::endpoint ep);
    ~server();
private:
    std::unique_ptr<server_pimpl> m_pimpl;
};

} // namespace chat
