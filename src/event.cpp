#include "../include/event.hpp"

namespace ux
{
    EventHandler::EventHandler()
    {
        id = seed++ ;
        focused = false ;
        callbacks[UXEvents::None].push_back(NO_EVENT_HANDLER) ;
    }

    EventID EventHandler::addEventListener(int event, const HandlerType& f)
    {
        LOG("Adding event listeners...");
        callbacks[event].push_back(f);
        LOG("Event Listeners added...");
        return EventID{event, callbacks[event].size() - 1, id};
    }

    bool EventHandler::removeEventListener(const EventID& eid)
    {
        if(id == eid.component_id)
        {
            callbacks[eid.event_type][eid.handler_id] = NO_EVENT_HANDLER ;
            return true ;
        }
        return false ;
    }

    unsigned int EventHandler::seed = 0 ;
    HandlerType EventHandler::NO_EVENT_HANDLER = [](Event const&){};
}
