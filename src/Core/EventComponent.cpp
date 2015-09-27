/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-04-15
**/


#include <Cucca/Core/EventComponent.hpp>


using namespace Cucca;


EventComponent::EventComponent(void) {
    events_[-1];
}

void EventComponent::pushEvent(std::shared_ptr<EventBase> event) {
    if (event->getEventType() != -1)
        events_[event->getEventType()].push_back(event);
}

void EventComponent::clearEvents(int eventTypeId) {
    if (eventTypeId != -1)
        events_[eventTypeId].clear();
}

const std::deque<std::shared_ptr<EventBase>>& EventComponent::getEvents(int eventTypeId) const {
    try {
        return events_.at(eventTypeId);
    }
    catch (...) {
        return events_.at(-1);
    }
}
