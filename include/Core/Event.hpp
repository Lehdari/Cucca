/**
    Cucca Game Engine - Core - Event.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Event class stores events of arbitrary type.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-26
**/


#ifndef CUCCA_CORE_EVENT_HPP
#define CUCCA_CORE_EVENT_HPP


#include "EventBase.hpp"

#include <memory>


namespace Cucca {
    template<typename EventType_T>
    class Event : public EventBase {
    public:
        Event(const EventType_T& event) :
            EventBase(event),
            event_(std::unique_ptr<EventType_T>(new EventType_T(event)))
        {}

        //  Get event pointer
        EventType_T* getEvent(void) const {
            return event_.get();
        }

    private:
        //  Stored event
        std::unique_ptr<EventType_T> event_;
    };
}


#endif // CUCCA_CORE_EVENT_HPP
