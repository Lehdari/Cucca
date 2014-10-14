#include "../../include/CoreExtensions/Canvas_SFML.hpp"


Canvas_SFML::Canvas_SFML(void)
{
    // window settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    window_.create(sf::VideoMode(800, 600), "Cucca", sf::Style::Default, settings);
    window_.setFramerateLimit(60);
}


void Canvas_SFML::display(void) {
    window_.display();
}

Event Canvas_SFML::pollEvent(void) {
    sf::Event event;
    window_.pollEvent(event);
    return Event(event);
}
