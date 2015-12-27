#include "../include/event.hpp"

namespace ux
{
    EventHandler::EventHandler()
    {
        m_id = seed++ ;
        m_focused = false ;
        m_callbacks[UXEvents::None].push_back(NO_EVENT_HANDLER) ;
    }

    EventID EventHandler::addEventListener(int event, const HandlerType& f)
    {
        START;
        m_callbacks[event].push_back(f);
        END;
        return EventID{event, m_callbacks[event].size() - 1, m_id};
    }

    bool EventHandler::removeEventListener(const EventID& eid)
    {
        if(m_id == eid.m_component_id)
        {
            m_callbacks[eid.m_event_type][eid.m_handler_id] = NO_EVENT_HANDLER ;
            return true ;
        }
        return false ;
    }

    unsigned int EventHandler::seed = 0 ;
    HandlerType EventHandler::NO_EVENT_HANDLER = [](Event const&){};
}
