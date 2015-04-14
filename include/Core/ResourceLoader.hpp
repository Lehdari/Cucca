/**
    Cucca Game Engine - Core - ResourceLoader.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceLoader is a visitor which (pre)loads resources according to
    ResourceLoadingEvent instances.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-04-15
**/


#ifndef CUCCA_CORE_RESOURCELOADER_HPP
#define CUCCA_CORE_RESOURCELOADER_HPP


#include "../Core/Visitor.hpp"
#include "../Core/EventComponent.hpp"


namespace Cucca {

    CUCCA_VISITOR(ResourceLoader, EventComponent) {
    public:
        void nodeEnter(Node* node, EventComponent* component);
        void nodeExit(Node* node, EventComponent* component) {}
    };

}


#endif // CUCCA_CORE_RESOURCELOADER_HPP
