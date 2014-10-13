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

    window_ = new sf::Window(sf::VideoMode(800, 600), "Cucca", sf::Style::Default, settings);
}

Canvas_SFML::~Canvas_SFML(void) {
    delete window_;
}
