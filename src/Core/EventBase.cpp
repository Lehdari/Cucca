#include "../../include/Core/EventBase.hpp"


/*EventBase::EventBase(void) :
    eventType_(-1)
    {}*/

int EventBase::getEventType(void) const {
    return eventType_;
}
