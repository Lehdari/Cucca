#ifndef CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP
#define CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP


#include "../Core/Canvas.hpp"

#include <memory>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>



class Canvas_SFML : public Canvas<Canvas_SFML> {
public:
    Canvas_SFML(void);
    ~Canvas_SFML(void) {}

    Event* pollEvent(void);

private:
    sf::Window window_;
};


#endif // CUCCA_COREEXTENSIONS_CANVAS_SFML_HPP
