#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


#include "../../include/Core/Device.hpp"
#include "../../include/Core/ThreadPool.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/CoreExtensions/Canvas_SFML.hpp"
#include "../../include/CoreExtensions/EventVisitor_SFML.hpp"
#include "../../include/Graphics/ShaderObject.hpp"


using namespace Cucca;


int unitTest(void) {
    //  First things first
    auto device = DEVICE(Canvas_SFML);

    ThreadPool pool;
    pool.launchThreads(2);

    ResourceManager<ResourceId> manager(device->getGraphicsTaskQueue(), pool.getTaskQueue());

    Node* root = device->getRoot();


    Node child;
    EventComponent sfmlEventComponent;

    child.addComponent(std::move(sfmlEventComponent));
    device->subscribeEvents(child.getComponents<EventComponent>().back(), EventBase::getEventTypeId<sf::Event>());
    root->addChild(std::move(child));


    //  Resources
    ResourceInitInfo<ShaderObject> vertexShaderInitInfo1;
    vertexShaderInitInfo1.source = ResourceInitInfo<ShaderObject>::SOURCE_CODE;
    vertexShaderInitInfo1.type = GL_VERTEX_SHADER;

    manager.addResourceInfo<ShaderObject>("SHADER_VERTEX_1", vertexShaderInitInfo1, std::vector<ResourceId>(), std::vector<ResourceId>(), true);
    auto vertexShader1 = manager.getResource<ShaderObject>("SHADER_VERTEX_1");


    //  Run it
    EventVisitor_SFML sfmlEventVisitor;

    while (device->status() == Device<Canvas_SFML>::STATUS_RUNNING) {
        device->render();
        device->handleEvents();
        device->getRoot()->accept(sfmlEventVisitor);
    }

    return 0;
}


#endif // CURRENT_TEST
