/**
    Cucca Game Engine - CoreExtensions - Canvas_SFML.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#include "../../include/CoreExtensions/Canvas_SFML.hpp"
#include "../../include/Core/Event.hpp"


using namespace Cucca;


Cucca::Canvas_SFML::Canvas_SFML(void)
{
    // window settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    window_.create(sf::VideoMode(1280, 720), "Cucca Game Engine", sf::Style::Default, settings);
    window_.setFramerateLimit(60);
}

bool Cucca::Canvas_SFML::isOpen(void) {
    return window_.isOpen();
}

void Cucca::Canvas_SFML::display(void) {
    window_.display();
}

void Cucca::Canvas_SFML::close(void) {
    window_.close();
}

std::shared_ptr<EventBase> Cucca::Canvas_SFML::pollEvent(void) {
    sf::Event event;
    if (window_.pollEvent(event))
        return std::shared_ptr<EventBase>(new Event<sf::Event>(event));
    else
        return std::shared_ptr<EventBase>(nullptr);
}

sf::Window* Canvas_SFML::getWindow(void) {
    return &window_;
}
