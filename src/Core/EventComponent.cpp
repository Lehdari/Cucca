/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#include "../../include/Core/EventComponent.hpp"


using namespace Cucca;


void Cucca::EventComponent::pushEvent(std::shared_ptr<EventBase> event) {
    eventQueue_.push(event);
}

std::shared_ptr<EventBase> Cucca::EventComponent::pullEvent(void) {
    if (eventQueue_.empty())
        return std::shared_ptr<EventBase>(nullptr);

    std::shared_ptr<EventBase> event = eventQueue_.front();
    eventQueue_.pop();
    return event;
}
