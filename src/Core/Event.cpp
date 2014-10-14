#include "../../include/Core/Event.hpp"


unsigned Event::numEventTypes__;


void* Event::getEvent(void) {
    return event_;
}

unsigned Event::getEventType(void) {
    return eventType_;
}
