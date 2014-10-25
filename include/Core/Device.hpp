/**
    Cucca Game Engine - Core - Device.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#ifndef CUCCA_CORE_DEVICE_HPP
#define CUCCA_CORE_DEVICE_HPP


#include "Node.hpp"
#include "Canvas.hpp"
#include "Event.hpp"
#include "EventComponent.hpp"

#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>

//  begin of TEMP
#include "../CoreExtensions/EventVisitor_SFML.hpp"
//  end of TEMP


namespace Cucca {
    template<typename CanvasType_T>
    class Device {
    public:
        static Device<CanvasType_T>* getInstance(void) {
            if (!instance__)
                instance__ = std::unique_ptr<Device<CanvasType_T>>(new Device<CanvasType_T>());
            return instance__.get();
        }

        void renderLoop(void) {
            while (canvas_.isOpen()) {
                eventLoop();
                canvas_.display();
            }
        }

        void eventLoop(void) {
            //  first poll events from canvas
            std::shared_ptr<EventBase> event = canvas_.pollEvent();

            while (event) {
                int eventType = event.get()->getEventType();
                for (auto& eventComponent : eventSubscribers_[eventType])
                    eventComponent->pushEvent(event);

                event = canvas_.pollEvent();
            }

            //  begin of TEMP
            root_->accept(eventVisitor_);
            //  end of TEMP
        }

        //  Terminate the device (shut down the application)
        void terminate(void) {
            canvas_.close();
        }

        //  Push an event into event queue
        void pushEvent(EventBase& event) {
            eventQueue_.push(std::make_shared<EventBase>(event));
        }

        //  Subscribe events of specific type (use EventBase::getEventTypeId for correct id)
        void subscribeEvents(EventComponent* eventComponent, int eventTypeId) {
            eventSubscribers_[eventTypeId].push_back(eventComponent);
        }

        //  Get pointer to root node
        Node* getRoot(void) {
            return root_.get();
        }

    private:
        //  Singleton pattern
        static std::unique_ptr<Device<CanvasType_T>> instance__;
        Device(void) :
            root_(std::unique_ptr<Node>(new Node()))
            {}
        Device<CanvasType_T>(const Device<CanvasType_T>&) {};
        Device<CanvasType_T>& operator=(const Device<CanvasType_T>&) {};

        //  Canvas
        CanvasType_T canvas_;

        //  Event queue
        std::queue<std::shared_ptr<EventBase>> eventQueue_;
        //  Event type id mapping for subcriptions
        std::unordered_map<int, std::vector<EventComponent*>> eventSubscribers_;

        //  Root node
        std::unique_ptr<Node> root_;

        //  begin of TEMP
        EventVisitor_SFML eventVisitor_;
        //  end of TEMP
    };

    template<typename CanvasType_T>
    std::unique_ptr<Device<CanvasType_T>> Device<CanvasType_T>::instance__ = std::unique_ptr<Device<CanvasType_T>>(nullptr);
}


#endif // CUCCA_CORE_DEVICE_HPP
