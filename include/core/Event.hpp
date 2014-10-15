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


#include "EventBase.hpp"


template<typename EventType_T>
class Event : public EventBase {
public:
    //  Constructors/destructors
    Event(const Event<EventType_T>& event) {
        EventBase(event.event_),
        event_ = event.event_;
        referenceCounter_ = event.referenceCounter_;
        ++*referenceCounter_;
    }

    Event(EventType_T& event) :
        EventBase(&event),
        event_(&event),
        referenceCounter_(new int(1))
    {}

    ~Event(void) {
        if (--*referenceCounter_ == 0) {
            delete event_;
            delete referenceCounter_;
        }
    }

    //  Get event pointer
    EventType_T* getEvent(void) const {
        return event_;
    }

    Event& operator=(const Event& event) {
        if (this != &event) {
            if (--*referenceCounter_ == 0) {
                delete event_;
                delete referenceCounter_;
            }
            event_ = event.event_;
            eventType_ = event.eventType_;
            referenceCounter_ = event.referenceCounter_;
            ++*referenceCounter_;
        }
        return this;
    }

private:
    //  Stored event and its type identifier and reference counter
    EventType_T* event_;
    int* referenceCounter_;
};


#endif // CUCCA_CORE_EVENT_HPP
