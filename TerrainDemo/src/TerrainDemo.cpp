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
    //  Vertex shader (VS)
    BinaryInitInfo_File terrainVSBinaryInitInfo;
    terrainVSBinaryInitInfo.fileName = "TerrainDemo/shaders/VS_Terrain.glsl";
    manager.addResourceInfo<Binary>("BINARY_VS_TERRAIN", terrainVSBinaryInitInfo);

    ShaderObjectInitInfo_Binary terrainVSInitInfo;
    terrainVSInitInfo.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    terrainVSInitInfo.type = GL_VERTEX_SHADER;
    manager.addResourceInfo<ShaderObject>("VS_TERRAIN",
                                          terrainVSInitInfo,
                                          std::vector<ResourceId>{ "BINARY_VS_TERRAIN" },
                                          std::vector<ResourceId>(),
                                          true);

    //  Tesselation control shader (TCS)
    BinaryInitInfo_File terrainTCSBinaryInitInfo;
    terrainTCSBinaryInitInfo.fileName = "TerrainDemo/shaders/TCS_Terrain.glsl";
    manager.addResourceInfo<Binary>("BINARY_TCS_TERRAIN", terrainTCSBinaryInitInfo);

    ShaderObjectInitInfo_Binary terrainTCSInitInfo;
    terrainTCSInitInfo.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    terrainTCSInitInfo.type = GL_TESS_CONTROL_SHADER;
    manager.addResourceInfo<ShaderObject>("TCS_TERRAIN",
                                          terrainTCSInitInfo,
                                          std::vector<ResourceId>{ "BINARY_TCS_TERRAIN" },
                                          std::vector<ResourceId>(),
                                          true);

    //  Tesselation evaluation shader (TES)
    BinaryInitInfo_File terrainTESBinaryInitInfo;
    terrainTESBinaryInitInfo.fileName = "TerrainDemo/shaders/TES_Terrain.glsl";
    manager.addResourceInfo<Binary>("BINARY_TES_TERRAIN", terrainTESBinaryInitInfo);

    ShaderObjectInitInfo_Binary terrainTESInitInfo;
    terrainTESInitInfo.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    terrainTESInitInfo.type = GL_TESS_EVALUATION_SHADER;
    manager.addResourceInfo<ShaderObject>("TES_TERRAIN",
                                          terrainTESInitInfo,
                                          std::vector<ResourceId>{ "BINARY_TES_TERRAIN" },
                                          std::vector<ResourceId>(),
                                          true);


    //  Fragment shader (FS)
    BinaryInitInfo_File terrainFSBinaryInitInfo;
    terrainFSBinaryInitInfo.fileName = "TerrainDemo/shaders/FS_Terrain.glsl";
    manager.addResourceInfo<Binary>("BINARY_FS_TERRAIN", terrainFSBinaryInitInfo);

    ShaderObjectInitInfo_Binary terrainFSInitInfo;
    terrainFSInitInfo.source = ShaderObjectInitInfo_Binary::SOURCE_GLSL;
    terrainFSInitInfo.type = GL_FRAGMENT_SHADER;
    manager.addResourceInfo<ShaderObject>("FS_TERRAIN",
                                          terrainFSInitInfo,
                                          std::vector<ResourceId>{ "BINARY_FS_TERRAIN" },
                                          std::vector<ResourceId>(),
                                          true);

    //  Shader program
    ShaderProgramInitInfo_Default terrainShaderInitInfo;
    manager.addResourceInfo<ShaderProgram>("SHADER_TERRAIN",
                                           terrainShaderInitInfo,
                                           std::vector<ResourceId>{ "VS_TERRAIN", "TCS_TERRAIN", "TES_TERRAIN", "FS_TERRAIN" },
                                           std::vector<ResourceId>(),
                                           true);

    //  Textures
    BinaryInitInfo_File terrainDiffuseBinaryInitInfo;
    terrainDiffuseBinaryInitInfo.fileName = "res/heightmaps/heightmap_diffuse_01.png";
    manager.addResourceInfo<Binary>("BINARY_DIFFUSE_TERRAIN", terrainDiffuseBinaryInitInfo);

    TextureInitInfo_Binary terrainDiffuseInitInfo;
    terrainDiffuseInitInfo.source = TextureInitInfo_Binary::SOURCE_BINARY_PNG;
    terrainDiffuseInitInfo.wrapS = GL_REPEAT;
    terrainDiffuseInitInfo.wrapT = GL_REPEAT;
    terrainDiffuseInitInfo.minFiltering = GL_LINEAR_MIPMAP_LINEAR;
    terrainDiffuseInitInfo.magFiltering = GL_LINEAR;
    manager.addResourceInfo<Texture>("DIFFUSE_TERRAIN",
                                     terrainDiffuseInitInfo,
                                     std::vector<ResourceId>{ "BINARY_DIFFUSE_TERRAIN" },
                                     std::vector<ResourceId>(),
                                     true);

    BinaryInitInfo_File terrainDisplacementBinaryInitInfo;
    terrainDisplacementBinaryInitInfo.fileName = "res/heightmaps/displacementMap_01.png";
    manager.addResourceInfo<Binary>("BINARY_DISPLACEMENT_TERRAIN", terrainDisplacementBinaryInitInfo);

    TextureInitInfo_Binary terrainDisplacementInitInfo;
    terrainDisplacementInitInfo.source = TextureInitInfo_Binary::SOURCE_BINARY_PNG;
    terrainDisplacementInitInfo.wrapS = GL_REPEAT;
    terrainDisplacementInitInfo.wrapT = GL_REPEAT;
    terrainDisplacementInitInfo.minFiltering = GL_LINEAR_MIPMAP_LINEAR;
    terrainDisplacementInitInfo.magFiltering = GL_LINEAR;
    manager.addResourceInfo<Texture>("DISPLACEMENT_TERRAIN",
                                     terrainDisplacementInitInfo,
                                     std::vector<ResourceId>{ "BINARY_DISPLACEMENT_TERRAIN" },
                                     std::vector<ResourceId>(),
                                     true);

    MaterialInitInfo_Default terrainMaterialInitInfo;
    terrainMaterialInitInfo.uniformSampler2DNames = std::vector<std::string>{ "diffuse", "displacementMap" };
    terrainMaterialInitInfo.uniformMat4Names = std::vector<std::string>{ "model", "camera" };
    manager.addResourceInfo<Material>("MATERIAL_TERRAIN",
                                      terrainMaterialInitInfo,
                                      std::vector<ResourceId>(),
                                      std::vector<ResourceId>{ "SHADER_TERRAIN", "DIFFUSE_TERRAIN", "DISPLACEMENT_TERRAIN" },
                                      true);

    BinaryInitInfo_File terrainHeightMapMajorBinaryInitInfo;
    terrainHeightMapMajorBinaryInitInfo.fileName = "res/heightmaps/heightmap_major_01.png";
    manager.addResourceInfo<Binary>("BINARY_HEIGHTMAP_MAJOR_TERRAIN", terrainHeightMapMajorBinaryInitInfo);

    HeightMapInitInfo_Default terrainHeightMapInitInfo;
    terrainHeightMapInitInfo.numXSegments = 128;
    terrainHeightMapInitInfo.numYSegments = 128;
    terrainHeightMapInitInfo.segmentXResolution = 4;
    terrainHeightMapInitInfo.segmentYResolution = 4;
    terrainHeightMapInitInfo.segmentXSize = 256.0f;
    terrainHeightMapInitInfo.segmentYSize = 256.0f;
    terrainHeightMapInitInfo.offsetX = -16384.0f;
    terrainHeightMapInitInfo.offsetY = -16384.0f;

    manager.addResourceInfo<HeightMap>("HEIGHTMAP_TERRAIN",
                                       terrainHeightMapInitInfo,
                                       std::vector<ResourceId>{ "BINARY_HEIGHTMAP_MAJOR_TERRAIN" },
                                       std::vector<ResourceId>());

    Terrain terrain(manager, root, "HEIGHTMAP_TERRAIN", "MATERIAL_TERRAIN", "TERRAINSEGMENT");

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
    camera.projection(1.5708f, 16.0f/9.0f, 0.05f, 1280.0f);

    EventVisitor_SFML sfmlEventVisitor;

    //  Run it
    while (device->status() == Device<Canvas_SFML>::STATUS_RUNNING) {
        device->handleEvents();
        device->getRoot()->accept(camera);
        device->getRoot()->accept(sfmlEventVisitor);
        device->render();

        terrain.update(camera.getPosition(), 1536.0f, 1280.0f);
    }

    return 0;
}


#endif // CURRENT_TEST
