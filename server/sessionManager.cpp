#include "sessionManager.h"
#include "session.h"
pSession sessionManager::newSession()
{
     return std::make_shared<session>(m_context, *this);
}


