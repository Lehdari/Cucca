/**
    Cucca Game Engine - Core - Event.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Event class serves as a shared smart pointer for different event types.
    Type information is stored in similar manner as in Nodes.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-14
**/


#ifndef CUCCA_CORE_EVENT_HPP
#define CUCCA_CORE_EVENT_HPP


class Event {
public:
    //  Standard consturctors/destructors
    Event(void);
    Event(const Event& event);
    ~Event(void);

    //  Template constructor
    template<typename EventType_T>
    Event(EventType_T& event) :
        event_(&event),
        eventType_(getEventTypeId<EventType_T>()),
        referenceCounter_(new int(1))
    {}

    //  Set event. Returns type of the event.
    template<typename EventType_T>
    int setEvent(const EventType_T& event) {
        event_ = &event;
        return eventType_ = getEventTypeId<EventType_T>();
    }

    //  Get event pointer
    void* getEvent(void) const;
    //  Get event type. Will return -1 if no event is stored.
    int getEventType(void) const;

    /*  Event type information system. For every new event type, an
        unique identifier will be created in compile-time. */
    template<typename EventType_T>
    static int getEventTypeId(void) {
        static int eventTypeId__ = numEventTypes__++;
        return eventTypeId__;
    }

    Event& operator=(const Event& event);

private:
    static unsigned numEventTypes__;

    //  Stored event and its type identifier and reference counter
    void* event_;
    int eventType_;
    int* referenceCounter_;
};


#endif // CUCCA_CORE_EVENT_HPP
