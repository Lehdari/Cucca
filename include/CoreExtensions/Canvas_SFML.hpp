/**
    Cucca Game Engine - CoreExtensions - Canvas_SFML.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Canvas_SFML class is an implementation of canvas interface for SFML
    library.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#ifndef CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP
#define CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP


#include "../Core/Canvas.hpp"

#include <SFML/Window.hpp>


namespace Cucca {
    class Canvas_SFML : public Canvas<Canvas_SFML> {
    public:
        Canvas_SFML(void);
        ~Canvas_SFML(void) {}

        bool isOpen(void);
        void display(void);
        void close(void);
        std::shared_ptr<EventBase> pollEvent(void);

    private:
        sf::Window window_;
    };
}


#endif // CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP
