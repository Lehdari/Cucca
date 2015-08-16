#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


//  TerrainDemo includes
#include "../include/Terrain.hpp"
#include "../include/HeightMap_Init_Default.hpp"

//  Cucca includes
#include "../../include/Core/Device.hpp"
#include "../../include/Core/ThreadPool.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary_Init_File.hpp"

#include "../../include/CoreExtensions/Canvas_SFML.hpp"
#include "../../include/CoreExtensions/EventVisitor_SFML.hpp"

#include "../../include/Graphics/ShaderObject_Init_Binary.hpp"
#include "../../include/Graphics/ShaderProgram_Init_Default.hpp"
#include "../../include/Graphics/Texture_Init_Binary.hpp"
#include "../../include/Graphics/Material_Init_Default.hpp"
#include "../../include/Graphics/VertexData_Init_Binary.hpp"
#include "../../include/Graphics/Mesh_Init_Default.hpp"
#include "../../include/Graphics/TransformationComponent.hpp"
#include "../../include/Graphics/MeshComponent.hpp"

#include "../../include/GraphicsExtensions/MovableCamera.hpp"

#include <random>
#include "../../include/Debug/Debug.hpp" // TEMP


#define rndf ((float)rnd() / rnd.max())


using namespace Cucca;


int terrainDemo(void) {
    //  First things first
    std::default_random_engine rnd;

    auto device = DEVICE(Canvas_SFML);
    device->getCanvas()->getWindow()->setKeyRepeatEnabled(false); // TEMP?
    device->getCanvas()->getWindow()->setFramerateLimit(60); // TEMP?

    /*GLenum err = */glewInit();

    ThreadPool pool;
    pool.launchThreads(2);

    ResourceManager<ResourceId> manager(device->getGraphicsTaskQueue(), pool.getTaskQueue());

    Node* root = device->getRoot();

    //  Shader
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

    //  Terrain
    BinaryInitInfo_File textureBinaryInitInfo2;
    textureBinaryInitInfo2.fileName = "res/heightmaps/heightmap_diffuse_01.png";
    manager.addResourceInfo<Binary>("BINARY_TEXTURE_2", textureBinaryInitInfo2);

    TextureInitInfo_Binary textureInitInfo2;
    textureInitInfo2.source = TextureInitInfo_Binary::SOURCE_BINARY_PNG;
    textureInitInfo2.wrapS = GL_REPEAT;
    textureInitInfo2.wrapT = GL_REPEAT;
    textureInitInfo2.minFiltering = GL_LINEAR_MIPMAP_LINEAR;
    textureInitInfo2.magFiltering = GL_LINEAR;
    manager.addResourceInfo<Texture>("TEXTURE_TERRAIN",
                                     textureInitInfo2,
                                     std::vector<ResourceId>{ "BINARY_TEXTURE_2" },
                                     std::vector<ResourceId>(),
                                     true);

    MaterialInitInfo_Default materialInitInfo2;
    manager.addResourceInfo<Material>("MATERIAL_TERRAIN",
                                      materialInitInfo2,
                                      std::vector<ResourceId>(),
                                      std::vector<ResourceId>{ "SHADER_PROGRAM_1", "TEXTURE_TERRAIN" },
                                      true);

    BinaryInitInfo_File heightMapMajorBinaryInitInfo;
    heightMapMajorBinaryInitInfo.fileName = "res/heightmaps/heightmap_major_01.png";
    manager.addResourceInfo<Binary>("BINARY_HEIGHTMAP_MAJOR", heightMapMajorBinaryInitInfo);

    HeightMapInitInfo_Default terrainHeightMapInitInfo;
    terrainHeightMapInitInfo.numXSegments = 256;
    terrainHeightMapInitInfo.numYSegments = 256;
    terrainHeightMapInitInfo.segmentXResolution = 32;
    terrainHeightMapInitInfo.segmentYResolution = 32;
    terrainHeightMapInitInfo.segmentXSize = 128.0f;
    terrainHeightMapInitInfo.segmentYSize = 128.0f;
    terrainHeightMapInitInfo.offsetX = -16384.0f;
    terrainHeightMapInitInfo.offsetY = -16384.0f;

    manager.addResourceInfo<HeightMap>("HEIGHTMAP",
                                       terrainHeightMapInitInfo,
                                       std::vector<ResourceId>{ "BINARY_HEIGHTMAP_MAJOR" },
                                       std::vector<ResourceId>());

    Terrain terrain(manager, root, "HEIGHTMAP", "MATERIAL_TERRAIN", "TERRAINSEGMENT");

    //  Nodes
    Node eventNode;
    eventNode.addComponent(EventComponent());
    device->subscribeEvents(eventNode.getComponents<EventComponent>().back(), EventBase::getEventTypeId<sf::Event>());
    root->addChild(std::move(eventNode));

    //  Visitors
    MovableCamera camera(device->getCanvas()->getWindow());
    camera.lookAt(Vector3Glf{ 0.0f, 5.0f, 10.0f },
                  Vector3Glf{ 0.0f, 0.0f, 0.0f },
                  Vector3Glf{ 0.0f, 1.0f, 0.0f });
    camera.projection(1.5708f, 4.0f/3.0f, 0.05f, 1024.0f);

    EventVisitor_SFML sfmlEventVisitor;

    //  Run it
    while (device->status() == Device<Canvas_SFML>::STATUS_RUNNING) {
        device->handleEvents();
        device->getRoot()->accept(camera);
        device->getRoot()->accept(sfmlEventVisitor);
        device->render();

        terrain.update(camera.getPosition(), 1024.0f, 800.0f);
    }

    return 0;
}


#endif // CURRENT_TEST
