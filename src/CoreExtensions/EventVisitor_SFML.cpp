/**
    Cucca Game Engine - CoreExtensions - EventVisitor_SFML.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    EventVisitor_SFML is a Visitor designed to handle SFML events.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#include <Cucca/CoreExtensions/EventVisitor_SFML.hpp>
#include <Cucca/Core/Event.hpp>

#include <Cucca/Core/Device.hpp> // TEMP?
#include <Cucca/CoreExtensions/Canvas_SFML.hpp> // TEMP?

#include <SFML/Window/Event.hpp>
#include <iostream> // TEMP


using namespace Cucca;


void EventVisitor_SFML::nodeEnter(Node* node, EventComponent* component) {
    auto events = component->getEvents(EventBase::getEventTypeId<sf::Event>());

    for (auto& eventBase : events) {
        if (!eventBase)
            return;

        sf::Event* event = static_cast<Event<sf::Event>*>(eventBase.get())->getEvent();

        switch (event->type) {
        case sf::Event::Closed:
            std::cout << "sf::Event::Closed" << std::endl; // TEMP
            Device<Canvas_SFML>::getInstance()->terminate();
        break;
        case sf::Event::MouseMoved:
            std::cout << "sf::Event::MouseMoved  x: " << event->mouseMove.x << ", y: " << event->mouseMove.y << std::endl;
        break;
        default:

        break;
        }
    }
}
