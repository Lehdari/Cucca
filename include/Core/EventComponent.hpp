/**
    Cucca Game Engine - Core - EventComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventComponent is a Component equipped with an event queue.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-04-15
**/


#ifndef CUCCA_CORE_EVENTCOMPONENT_HPP
#define CUCCA_CORE_EVENTCOMPONENT_HPP


#include <Cucca/Core/Component.hpp>
#include <Cucca/Core/EventBase.hpp>

#include <unordered_map>
#include <deque>
#include <memory>


namespace Cucca {

    class EventComponent : public Component {
    public:
        EventComponent(void);

        void pushEvent(std::shared_ptr<EventBase> event);

        //  Clear events of specific type (use EventBase::getEventTypeId for correct id)
        void clearEvents(int eventTypeId);

        //  Get events of specific type (use EventBase::getEventTypeId for correct id)
        const std::deque<std::shared_ptr<EventBase>>& getEvents(int eventTypeId) const;

    private:
        std::unordered_map<int, std::deque<std::shared_ptr<EventBase>>> events_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_EVENTCOMPONENT_HPP
