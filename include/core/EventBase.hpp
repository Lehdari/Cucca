/**
    Cucca Game Engine - Core - EventBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventBase class acts as a base class for templated Event objects.
    It has a type identifier system similar to Node class. @see Node.hpp

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-15
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

    /*  Template constructor
        Constructors cannot be called with template parameters, that's why
        an argument is required for automatic deduction */
    template<typename EventType_T>
    EventBase(EventType_T* event) :
        eventType_(getEventTypeId<EventType_T>())
        {}

    //  Get event type. Will return -1 if no event is stored.
    int getEventType(void) const;

    //  Event Type system. Similar to the one in the Node class.
    template<typename EventType_T>
    static int getEventTypeId(void) {
        static unsigned numEventTypes__ = 0;
        static int eventTypeId__ = numEventTypes__++;
        return eventTypeId__;
    }

protected:
    //  Stored event type identifier
    int eventType_;
};


#endif // CUCCA_CORE_EVENTBASE_HPP
