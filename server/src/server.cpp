#include "chat/server.h"
#include "server_impl.h"
namespace chat {

server::server(asio::io_context &context, asio::ip::tcp::endpoint ep) :
    m_pimpl {std::make_unique<server_pimpl>(context, ep)}
{

}
server::~server() = default;

}
