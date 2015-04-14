/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-04-15
**/


#include "../../include/Core/EventComponent.hpp"


using namespace Cucca;


void EventComponent::pushEvent(std::shared_ptr<EventBase> event) {
    if (event->getEventType() != -1)
        events_[event->getEventType()].push_back(event);
}

void EventComponent::clearEvents(void) {
    events_.clear();
}

void EventComponent::clearEvents(int eventTypeId) {
    events_[eventTypeId].clear();
}

const std::deque<std::shared_ptr<EventBase>>& EventComponent::getEvents(int eventTypeId) const {
    return events_.at(eventTypeId);
}
