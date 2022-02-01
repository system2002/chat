#pragma once
#include <unordered_set>
#include <memory>
#include <asio.hpp>
#include "session.h"

namespace chat {
using pSession = std::shared_ptr<session>;

class sessionManager
{
public:
    sessionManager(asio::io_context &context) :
        m_context {context}
    {}

    bool contains(pSession session) const;
    void insert(pSession session) { m_sessions.insert(session); }
    void erase(pSession session);
    size_t count() const {return m_sessions.size();}
    pSession newSession();
    void printCount();

    template<typename Buffer_t>
    void sendNotMe(const pSession &me, Buffer_t &&buffer)
    {
        for (const pSession & currSession : m_sessions)
        {
            if (currSession != me)
            {
                currSession->asyncSendData(std::forward<Buffer_t>(buffer));
            }
        }
    }
    template<typename Buffer_t>
    void sendAll(Buffer_t &&buffer)
    {
        for (const pSession & currSession : m_sessions)
        {
            currSession->asyncSendData(std::forward<Buffer_t>(buffer));
        }
    }

private:
    std::unordered_set<pSession> m_sessions;
    asio::io_context & m_context;
};
}
