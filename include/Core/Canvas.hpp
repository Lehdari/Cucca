/**
    Cucca Game Engine - Core - Event.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Canvas is the interface between core and the system. An implementation
    of canvas must offer the functionality described by Canvas CRTP class.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#ifndef CUCCA_CORE_CANVAS_HPP
#define CUCCA_CORE_CANVAS_HPP


#include "EventBase.hpp"

#include <memory>


namespace Cucca {
    template<typename CanvasType_T>
    class Canvas {
    public:
        Canvas(void) {}
        ~Canvas(void) {}

        bool isOpen(void) {
            return static_cast<CanvasType_T*>(this)->isOpen();
        }

        void display(void) {
            static_cast<CanvasType_T*>(this)->display();
        }

        void close(void) {
            static_cast<CanvasType_T*>(this)->close();
        }

        std::shared_ptr<EventBase> pollEvent(void) {
            return static_cast<CanvasType_T*>(this)->pollEvent();
        }
    };
}


#endif // CUCCA_CORE_CANVAS_HPP
