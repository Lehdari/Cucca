/**
    Cucca Game Engine - Core - EventComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventComponent is a Component equipped with an event queue.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-16
**/


#ifndef CUCCA_CORE_EVENTCOMPONENT_HPP
#define CUCCA_CORE_EVENTCOMPONENT_HPP


#include "Component.hpp"
#include "EventBase.hpp"

#include <queue>
#include <memory>


class EventComponent : public Component {
public:
    void pushEvent(std::shared_ptr<EventBase> event);
    std::shared_ptr<EventBase> pullEvent(void);

private:
    std::queue<std::shared_ptr<EventBase>> eventQueue_;
};


#endif // CUCCA_CORE_EVENTCOMPONENT_HPP
