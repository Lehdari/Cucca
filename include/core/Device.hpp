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


#include "Canvas.hpp"


template<typename CanvasType_T>
class Device {
public:
    Device(void) {};
    ~Device(void);

private:
    CanvasType_T canvas_;
};


#endif // CUCCA_CORE_DEVICE_HPP
