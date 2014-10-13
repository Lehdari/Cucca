#include "../../include/Core/Event.hpp"


void* Event::getEvent(void) {
    return event_;
}

unsigned Event::getEventType(void) {
    return eventType_;
}
