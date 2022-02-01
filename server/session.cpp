#include "session.h"
#include "sessionManager.h"


void session::closeSession()
{
    auto self = shared_from_this();
    m_manager.erase(shared_from_this());
}
