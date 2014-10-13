/**
    Cucca Game Engine - Core - Event.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Event class serves as a container for different event types.
    Type information is stored in similar manner as in Nodes.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-13
**/


#ifndef CUCCA_CORE_EVENT_HPP
#define CUCCA_CORE_EVENT_HPP


class Event {
public:
    template<typename EventType_T>
    unsigned setEvent(EventType_T* event) {
        eventType_ = getEventTypeId<EventType_T>();
    }

    void* getEvent(void);
    unsigned getEventType(void);

private:
    /*  Event type information system. For every new event type, an
        unique identifier will be created in compile-time. */
    static unsigned numEventTypes__;

    template<typename EventType_T>
    static unsigned getEventTypeId(void) {
        static unsigned eventTypeId__ = numEventTypes__++;
        return eventTypeId__;
    }

    //  Stored event and its type identifier
    void* event_;
    unsigned eventType_;
};

unsigned Event::numEventTypes__;


#endif // CUCCA_CORE_EVENT_HPP
