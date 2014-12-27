#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


#include "../../include/Core/Device.hpp"
#include "../../include/Core/ThreadPool.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/CoreExtensions/Canvas_SFML.hpp"
#include "../../include/CoreExtensions/EventVisitor_SFML.hpp"
#include "../../include/Core/Binary.hpp"
#include "../../include/Graphics/ShaderObject.hpp"
#include "../../include/Graphics/ShaderProgram.hpp"


using namespace Cucca;


int unitTest(void) {
    //  First things first
    auto device = DEVICE(Canvas_SFML);
    GLenum err = glewInit();

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
    ResourceInitInfo<Binary> vertexShaderBinaryInitInfo1;
    vertexShaderBinaryInitInfo1.source = ResourceInitInfo<Binary>::SOURCE_FILE;
    vertexShaderBinaryInitInfo1.fileName = "res/shaders/VS_Simple.glsl";
    manager.addResourceInfo<Binary>("BINARY_SHADER_VERTEX_1", vertexShaderBinaryInitInfo1);

    ResourceInitInfo<Binary> fragmentShaderBinaryInitInfo1;
    fragmentShaderBinaryInitInfo1.source = ResourceInitInfo<Binary>::SOURCE_FILE;
    fragmentShaderBinaryInitInfo1.fileName = "res/shaders/FS_Simple.glsl";
    manager.addResourceInfo<Binary>("BINARY_SHADER_FRAGMENT_1", fragmentShaderBinaryInitInfo1);

    ResourceInitInfo<ShaderObject> vertexShaderInitInfo1;
    vertexShaderInitInfo1.source = ResourceInitInfo<ShaderObject>::SOURCE_CODE;
    vertexShaderInitInfo1.type = GL_VERTEX_SHADER;
    manager.addResourceInfo<ShaderObject>("SHADER_VERTEX_1",
                                          vertexShaderInitInfo1,
                                          std::vector<ResourceId>{ "BINARY_SHADER_VERTEX_1" },
                                          std::vector<ResourceId>(),
                                          true);

    ResourceInitInfo<ShaderObject> fragmentShaderInitInfo1;
    fragmentShaderInitInfo1.source = ResourceInitInfo<ShaderObject>::SOURCE_CODE;
    fragmentShaderInitInfo1.type = GL_FRAGMENT_SHADER;
    manager.addResourceInfo<ShaderObject>("SHADER_FRAGMENT_1",
                                          fragmentShaderInitInfo1,
                                          std::vector<ResourceId>{ "BINARY_SHADER_FRAGMENT_1" },
                                          std::vector<ResourceId>(),
                                          true);

    ResourceInitInfo<ShaderProgram> shaderProgramInitInfo1;
    manager.addResourceInfo<ShaderProgram>("SHADER_PROGRAM_1",
                                           shaderProgramInitInfo1,
                                           std::vector<ResourceId>{ "SHADER_VERTEX_1", "SHADER_FRAGMENT_1" },
                                           std::vector<ResourceId>(),
                                           true);

    auto shader1 = manager.getResource<ShaderProgram>("SHADER_PROGRAM_1");

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
