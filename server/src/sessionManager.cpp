#include "sessionManager.h"
#include "session.h"
namespace chat {

bool sessionManager::contains(pSession session) const
{
    for (auto it = m_sessions.cbegin(); it != m_sessions.cend(); ++it)
    {
        if (session == *it) return true;
    }
    return false;
}

void sessionManager::erase(pSession session)
{
    if (contains(session))
    {
        m_sessions.erase(session);
    }
}

pSession sessionManager::newSession()
{
    return std::make_shared<session>(m_context, *this);
}

void sessionManager::printCount()
{
    std::cout << "Client count: " << count() << std::endl;
}
}
