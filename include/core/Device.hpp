/**
    Cucca Game Engine - Core - Device.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.



    @version    0.1
    @author     Miika Lehtimäki
    @date
**/


#ifndef CUCCA_CORE_DEVICE_HPP
#define CUCCA_CORE_DEVICE_HPP


#include "Node.hpp"
#include "Canvas.hpp"
#include "Event.hpp"

#include <queue>


template<typename CanvasType_T>
class Device {
public:
    Device(void) {};
    ~Device(void);

    void renderLoop(void) {

    }

    void eventLoop(void) {

    }

    // Push an event into event queue
    void pushEvent(Event& event) {
        eventQueue_.push_back(std::make_shared(event));
    }

private:
    Node* root_;
    CanvasType_T canvas_;

    std::queue<std::shared_ptr<Event>> eventQueue_;
};


#endif // CUCCA_CORE_DEVICE_HPP
