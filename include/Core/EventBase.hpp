/**
    Cucca Game Engine - Core - EventBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventBase class acts as a base class for templated Events.
    It has a type identifier system similar to Node class. @see Node.hpp

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-26
**/


#ifndef CUCCA_CORE_EVENTBASE_HPP
#define CUCCA_CORE_EVENTBASE_HPP


class EventBase {
public:
    //  Standard constructors/destructors
    EventBase(void) :
        eventType_(-1)
        {}
    virtual ~EventBase(void) {}

    //  Get event type. Will return -1 if no event is stored.
    int getEventType(void) const;

    //  Event type id system. Similar to the one in the Node class.
    template<typename EventType_T>
    static int getEventTypeId(void) {
        static unsigned numEventTypes__ = 0;
        static int eventTypeId__ = numEventTypes__++;
        return eventTypeId__;
    }

protected:
    /*  Template constructor
        Constructors cannot be called with template parameters, that's why
        an argument is required for automatic deduction. */
    template<typename EventType_T>
    EventBase(const EventType_T& event) :
        eventType_(getEventTypeId<EventType_T>())
        {}

    //  Stored event type identifier
    int eventType_;
};


#endif // CUCCA_CORE_EVENTBASE_HPP
