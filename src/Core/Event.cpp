/**
    Cucca Game Engine - Core - Event.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Event class serves as a shared smart pointer for different event types.
    Type information is stored in similar manner as in Nodes.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-14
**/


#include "../../include/Core/Event.hpp"


unsigned Event::numEventTypes__;


Event::Event(void) :
    event_(nullptr),
    eventType_(-1),
    referenceCounter_(new int(1))

{}

Event::Event(const Event& event) {
    event_ = event.event_;
    eventType_ = event.eventType_;
    referenceCounter_ = event.referenceCounter_;
    ++*referenceCounter_;
}

Event::~Event(void) {
    if (--*referenceCounter_ == 0) {
        delete event_;
        delete referenceCounter_;
    }
}

void* Event::getEvent(void) const {
    return event_;
}

int Event::getEventType(void) const {
    return eventType_;
}

Event& Event::operator=(const Event& event) {
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
