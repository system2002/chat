#pragma once
#include <set>
#include <memory>
#include <asio.hpp>

class session;
using pSession = std::shared_ptr<session>;

class sessionManager
{
public:
    sessionManager(asio::io_context &context) :
        m_context {context}
    {}


    bool contains(pSession session)
    {
        for (auto it = m_sessions.cbegin(); it != m_sessions.cend(); ++it)
        {
            if (session == *it) return true;
        }
        return false;

    }
    void insert(pSession session) { m_sessions.insert(session); }
    void erase(pSession session)
    {
        if (contains(session))
        {
            m_sessions.erase(session);
        }
    }
    size_t count() {return m_sessions.size();}
    pSession newSession();

private:
    std::set<pSession> m_sessions;
    asio::io_context & m_context;
};

