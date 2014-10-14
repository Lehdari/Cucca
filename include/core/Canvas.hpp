#ifndef CUCCA_CORE_CANVAS_HPP
#define CUCCA_CORE_CANVAS_HPP


#include "Event.hpp"


template<typename CanvasType_T>
class Canvas {
public:
    Canvas(void) {}
    ~Canvas(void) {}

    Event* pollEvent(void) {
        return static_cast<CanvasType_T*>(this)->pollEvent();
    }
};


#endif // CUCCA_CORE_CANVAS_HPP
