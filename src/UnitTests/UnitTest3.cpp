#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


#include "../../include/Core/Device.hpp"
#include "../../include/CoreExtensions/Canvas_SFML.hpp"
#include "../../include/CoreExtensions/EventVisitor_SFML.hpp"


using namespace Cucca;


int unitTest(void) {
    Device<Canvas_SFML>* device = Device<Canvas_SFML>::getInstance();

    Node* root = device->getRoot();

    Node child;
    EventComponent sfmlEventComponent;

    child.addComponent(std::move(sfmlEventComponent));
    device->subscribeEvents(child.getComponents<EventComponent>().back(), EventBase::getEventTypeId<sf::Event>());
    root->addChild(std::move(child));

    device->renderLoop();
    return 0;
}


#endif // CURRENT_TEST
