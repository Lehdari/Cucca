#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


#include <Cucca/Core/Device.hpp>
#include <Cucca/Core/ThreadPool.hpp>
#include <Cucca/Core/ResourceManager.hpp>
#include <Cucca/Core/Binary_Init_File.hpp>

#include <Cucca/CoreExtensions/Canvas_SFML.hpp>
#include <Cucca/CoreExtensions/EventVisitor_SFML.hpp>

#include <Cucca/Graphics/ShaderObject_Init_Binary.hpp>
#include <Cucca/Graphics/ShaderProgram_Init_Default.hpp>
#include <Cucca/Graphics/Texture_Init_Binary.hpp>
#include <Cucca/Graphics/Material_Init_Default.hpp>
#include <Cucca/Graphics/VertexData_Init_Binary.hpp>
#include <Cucca/Graphics/Mesh_Init_Default.hpp>
#include <Cucca/Graphics/TransformationComponent.hpp>
#include <Cucca/Graphics/MeshComponent.hpp>
#include <Cucca/Graphics/BasicCamera.hpp>

#include <random>
#include <Cucca/Debug/Debug.hpp> // TEMP


#define rndf ((float)rnd() / rnd.max())


using namespace Cucca;


int unitTest(void) {
    //  First things first
    std::default_random_engine rnd;

    auto device = DEVICE(Canvas_SFML);
    device->getCanvas()->getWindow()->setKeyRepeatEnabled(false); // TEMP?
    //device->getCanvas()->getWindow()->setFramerateLimit(60); // TEMP?

    /*GLenum err = */glewInit();

    ThreadPool pool;
    pool.launchThreads(2);

    ResourceManager<ResourceId> manager(device->getGraphicsTaskQueue(), pool.getTaskQueue());

    Node* root = device->getRoot();

    //  Resources
    BinaryInitInfo_File vertexShaderBinaryInitInfo1;
    vertexShaderBinaryInitInfo1.fileName = "src/shaders/VS_SingleTexture.glsl";
    manager.addResourceInfo<Binary>("BINARY_SHADER_VERTEX_1", vertexShaderBinaryInitInfo1);

    BinaryInitInfo_File fragmentShaderBinaryInitInfo1;
    fragmentShaderBinaryInitInfo1.fileName = "src/shaders/FS_SingleTexture.glsl";
    manager.addResourceInfo<Binary>("BINARY_SHADER_FRAGMENT_1", fragmentShaderBinaryInitInfo1);

    ShaderObjectInitInfo_Binary vertexShaderInitInfo1;
    vertexShaderInitInfo1.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    vertexShaderInitInfo1.type = GL_VERTEX_SHADER;
    manager.addResourceInfo<ShaderObject>("SHADER_VERTEX_1",
                                          vertexShaderInitInfo1,
                                          std::vector<ResourceId>{ "BINARY_SHADER_VERTEX_1" },
                                          std::vector<ResourceId>(),
                                          true);

    ShaderObjectInitInfo_Binary fragmentShaderInitInfo1;
    fragmentShaderInitInfo1.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    fragmentShaderInitInfo1.type = GL_FRAGMENT_SHADER;
    manager.addResourceInfo<ShaderObject>("SHADER_FRAGMENT_1",
                                          fragmentShaderInitInfo1,
                                          std::vector<ResourceId>{ "BINARY_SHADER_FRAGMENT_1" },
                                          std::vector<ResourceId>(),
                                          true);

    ShaderProgramInitInfo_Default shaderProgramInitInfo1;
    manager.addResourceInfo<ShaderProgram>("SHADER_PROGRAM_1",
                                           shaderProgramInitInfo1,
                                           std::vector<ResourceId>{ "SHADER_VERTEX_1", "SHADER_FRAGMENT_1" },
                                           std::vector<ResourceId>(),
                                           true);

    BinaryInitInfo_File textureBinaryInitInfo1;
    textureBinaryInitInfo1.fileName = "res/models/cube.png";
    manager.addResourceInfo<Binary>("BINARY_TEXTURE_1", textureBinaryInitInfo1);

    TextureInitInfo_Binary textureInitInfo1;
    textureInitInfo1.source = TextureInitInfo_Binary::SOURCE_BINARY_PNG;
    textureInitInfo1.wrapS = GL_REPEAT;
    textureInitInfo1.wrapT = GL_REPEAT;
    textureInitInfo1.minFiltering = GL_LINEAR_MIPMAP_LINEAR;
    textureInitInfo1.magFiltering = GL_LINEAR;
    manager.addResourceInfo<Texture>("TEXTURE_1",
                                     textureInitInfo1,
                                     std::vector<ResourceId>{ "BINARY_TEXTURE_1" },
                                     std::vector<ResourceId>(),
                                     true);

    MaterialInitInfo_Default materialInitInfo1;
        materialInitInfo1.uniformSampler2DNames = { "diffuse" };
        materialInitInfo1.uniformMat4Names = { "MVP" };
    manager.addResourceInfo<Material>("MATERIAL_1",
                                      materialInitInfo1,
                                      std::vector<ResourceId>(),
                                      std::vector<ResourceId>{ "SHADER_PROGRAM_1", "TEXTURE_1" },
                                      true);

    BinaryInitInfo_File vertexDataBinaryInitInfo1;
    vertexDataBinaryInitInfo1.fileName = "res/models/cube.obj";
    manager.addResourceInfo<Binary>("BINARY_VERTEX_DATA_1", vertexDataBinaryInitInfo1);

    VertexDataInitInfo_Binary vertexDataInitInfo1;
    vertexDataInitInfo1.source = VertexDataInitInfo_Binary::SOURCE_BINARY_OBJ;
    manager.addResourceInfo<VertexData>("VERTEX_DATA_1",
                                        vertexDataInitInfo1,
                                        std::vector<ResourceId>{ "BINARY_VERTEX_DATA_1" },
                                        std::vector<ResourceId>());

    MeshInitInfo_Default meshInitInfo1;
    manager.addResourceInfo<Mesh>("MESH_1",
                                  meshInitInfo1,
                                  std::vector<ResourceId>{ "VERTEX_DATA_1" },
                                  std::vector<ResourceId>{ "MATERIAL_1" },
                                  true);

    auto mesh1 = manager.getResource<Mesh>("MESH_1");

    //  Nodes
    Node eventNode;
    eventNode.addComponent(EventComponent());
    device->subscribeEvents(eventNode.getComponents<EventComponent>().back(), EventBase::getEventTypeId<sf::Event>());
    root->addChild(std::move(eventNode));

    for (auto i=0u; i<100; ++i) {
        Node graphicsNode;
        graphicsNode.addComponent(TransformationComponent());
        graphicsNode.getComponents<TransformationComponent>().back()->translate(Vector3Glf{ 25.0f - 50.0f*rndf, 5.0f - 10.0f*rndf, 25.0f - 50.0f*rndf }, true);
        graphicsNode.addComponent(MeshComponent(mesh1));
        root->addChild(std::move(graphicsNode));
    }

    //  Visitors
    BasicCamera camera;
    camera.projection(1.5708f, 16.0f/9.0f, 0.05f, 1024.0f);
    camera.lookAt(Vector3Glf{ 0.0f, 5.0f, 25.0f },
                  Vector3Glf{ 0.0f, 0.0f, 0.0f },
                  Vector3Glf{ 0.0f, 1.0f, 0.0f });

    //EventVisitor_SFML sfmlEventVisitor;

    //  Some variables
    float t(0.0f);

    //  Run it
    while (device->status() == Device<Canvas_SFML>::STATUS_RUNNING) {
        device->handleEvents();
        device->getRoot()->accept(camera);
        //device->getRoot()->accept(sfmlEventVisitor);
        device->render();


        t += 0.001f;
        camera.lookAt(Vector3Glf{ 20.0f*cosf(t*2.0f), 0.0f + 5.0f*sinf(t*1.276f), 20.0f*sinf(t*2.0f) },
                      Vector3Glf{ 0.0f, 0.0f, 0.0f },
                      Vector3Glf{ 0.0f, 1.0f, 0.0f });
    }

    return 0;
}


#endif // CURRENT_TEST
