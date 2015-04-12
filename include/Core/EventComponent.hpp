/**
    Cucca Game Engine - Core - EventComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventComponent is a Component equipped with an event queue.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-19
**/


#ifndef CUCCA_CORE_EVENTCOMPONENT_HPP
#define CUCCA_CORE_EVENTCOMPONENT_HPP


#include "Component.hpp"
#include "EventBase.hpp"

#include <deque>
#include <memory>


namespace Cucca {

    class EventComponent : public Component {
    public:
        void pushEvent(std::shared_ptr<EventBase> event);
        std::shared_ptr<EventBase> pullEvent(void);
        void clearEvents(void);

        const std::deque<std::shared_ptr<EventBase>>& getEvents(void) const;
    private:
        std::deque<std::shared_ptr<EventBase>> events_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_EVENTCOMPONENT_HPP
