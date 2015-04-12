/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-19
**/


#include "../../include/Core/EventComponent.hpp"


using namespace Cucca;


void EventComponent::pushEvent(std::shared_ptr<EventBase> event) {
    events_.push_back(event);
}

std::shared_ptr<EventBase> EventComponent::pullEvent(void) {
    if (events_.empty())
        return std::shared_ptr<EventBase>(nullptr);

    std::shared_ptr<EventBase> event = events_.front();
    events_.pop_front();
    return event;
}

void EventComponent::clearEvents(void) {
    events_.clear();
}

const std::deque<std::shared_ptr<EventBase>>& EventComponent::getEvents(void) const {
    return events_;
}
