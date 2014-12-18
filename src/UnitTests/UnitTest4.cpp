#include "../../include/UnitTests/UnitTest4.hpp"


#if CURRENT_TEST == 4


#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"

#include <iostream>
#include <sstream>
#include <random>


using namespace Cucca;


TestResource_Vec2f::~TestResource_Vec2f(void) {
    std::cout << "~TestResource_Vec2f" << std::endl;
}

void TestResource_Vec2f::init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                              ResourceManager<ResourceId>& resourceManager,
                              const std::vector<ResourceId>& initResources,
                              const std::vector<ResourceId>& depResources) {
    std::cout << "TestResource_Vec2f::init" << std::endl;
    a_ = initInfo.a;
    b_ = initInfo.b;

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // so effect of threading is more noticeable
}

void TestResource_Vec2f::destroy(void) {
    std::cout << "TestResource_Vec2f::destroy" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // so effect of threading is more noticeable
}


TestResource_Movement::~TestResource_Movement(void) {
    std::cout << "~TestResource_Movement" << std::endl;
}

void TestResource_Movement::init(const ResourceInitInfo<TestResource_Movement>& initInfo,
                                 ResourceManager<ResourceId>& resourceManager,
                                 const std::vector<ResourceId>& initResources,
                                 const std::vector<ResourceId>& depResources) {
    std::cout << "TestResource_Movement::init" << std::endl;
    if (depResources.size() < 3)
        throw "TestResource_Movement: unable to initialize resource (insufficient dependency resources provided)"; // TODO_EXCEPTION: throw a proper exception

    position_ = resourceManager.getResource<TestResource_Vec2f>(depResources[0]);
    velocity_ = resourceManager.getResource<TestResource_Vec2f>(depResources[1]);
    acceleration_ = resourceManager.getResource<TestResource_Vec2f>(depResources[2]);
}

void TestResource_Movement::destroy(void) {
    std::cout << "TestResource_Movement::destroy" << std::endl;
}


TestResource_Vec2fTree::~TestResource_Vec2fTree(void) {
    std::cout << "~TestResource_Vec2fTree" << std::endl;
}

void TestResource_Vec2fTree::init(const ResourceInitInfo<TestResource_Vec2fTree>& initInfo,
                                 ResourceManager<ResourceId>& resourceManager,
                                 const std::vector<ResourceId>& initResources,
                                 const std::vector<ResourceId>& depResources) {
    std::cout << "TestResource_Vec2fTree::init" << std::endl;
    if (depResources.size() == 0)
        return;

    if (depResources.size() < 3)
        throw "TestResource_Vec2fTree: unable to initialize resource (insufficient dependency resources provided)"; // TODO_EXCEPTION: throw a proper exception

    if (depResources[0] != "")
        leftNode_ = resourceManager.getResource<TestResource_Vec2fTree>(depResources[0]);
    if (depResources[1] != "")
        rightNode_ = resourceManager.getResource<TestResource_Vec2fTree>(depResources[1]);
    if (depResources[2] != "")
        data_ = resourceManager.getResource<TestResource_Vec2f>(depResources[2]);

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // so effect of threading is more noticeable
}

void TestResource_Vec2fTree::destroy(void) {
    std::cout << "TestResource_Vec2fTree::destroy" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // so effect of threading is more noticeable
}


std::default_random_engine rnd(715517);


ResourceId makeRecursiveVec2fTreeInfo(ResourceManager<ResourceId>& resourceManager, unsigned* nodeId, unsigned* vec2fId, unsigned layer) {
    bool createdNodeId(false), createdVec2fId(false);

    if (!nodeId) {
        nodeId = new unsigned(0);
        createdNodeId = true;
    }

    if (!vec2fId) {
        vec2fId = new unsigned(0);
        createdVec2fId = true;
    }


    std::stringstream nodeName;
    nodeName << "NODE_" << (*nodeId)++;

    ResourceId leftNodeName, rightNodeName;
    std::stringstream dataName;

    if (rnd() % ((layer/2)+1) == 0) {
        leftNodeName = makeRecursiveVec2fTreeInfo(resourceManager, nodeId, vec2fId, layer+1);
        //std::cout << leftNodeName << std::endl;
    }

    if (rnd() % ((layer/2)+1) == 0) {
        rightNodeName = makeRecursiveVec2fTreeInfo(resourceManager, nodeId, vec2fId, layer+1);
        //std::cout << rightNodeName << std::endl;
    }

    if (rnd() % 3 != 0) {
        dataName << "VEC2F_" << (*vec2fId)++;

        ResourceInitInfo<TestResource_Vec2f> dataInfo;
        dataInfo.a = (rnd() % 101) / 100.0f;
        dataInfo.b = (rnd() % 101) / 100.0f;

        resourceManager.addResourceInfo(dataName.str(), dataInfo);
        //std::cout << dataName.str() << std::endl;
    }

    resourceManager.addResourceInfo(nodeName.str(),
                                    ResourceInitInfo<TestResource_Vec2fTree>(),
                                    std::vector<ResourceId>(),
                                    std::vector<ResourceId>{ leftNodeName, rightNodeName, dataName.str() });

    if (createdNodeId)
        delete nodeId;

    if (createdVec2fId)
        delete vec2fId;

    return nodeName.str();
}

int unitTest(void) {
    auto testPart = 0u;

    {   //  resource management basics
        std::cout << "[ Test Part " << ++testPart << " ]" << std::endl;
        ResourceManager<ResourceId> manager;

        ResourceInitInfo<TestResource_Vec2f> vecInfo1;
        vecInfo1.a = 0.25f;
        vecInfo1.b = 0.50f;
        ResourceInitInfo<TestResource_Vec2f> vecInfo2;
        vecInfo2.a = -0.45f;
        vecInfo2.b = -0.20f;
        ResourceInitInfo<TestResource_Vec2f> vecInfo3;
        vecInfo3.a = -0.7f;
        vecInfo3.b = 0.65f;

        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_1", vecInfo1);
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_2", vecInfo2);
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_3", vecInfo3);
        manager.addResourceInfo<TestResource_Movement>("MOVEMENT_1",
                                                       ResourceInitInfo<TestResource_Movement>(),
                                                       std::vector<ResourceId>(),
                                                       std::vector<ResourceId> {"VEC2F_1", "VEC2F_2", "VEC2F_3"});

        // RO5 tests
        auto vec_ref1 = manager.getResource<TestResource_Vec2f>("VEC2F_1");
        auto vec_ref2 = manager.getResource<TestResource_Vec2f>("VEC2F_1");
        auto vec_ref3 = manager.getResource<TestResource_Vec2f>("VEC2F_2");
        auto vec_ref4 = manager.getResource<TestResource_Vec2f>("VEC2F_2");
        auto vec_ref5(vec_ref1);
        auto vec_ref6(std::move(vec_ref1));
        auto vec_ref7 = vec_ref2;
        auto vec_ref8 = std::move(vec_ref2);
        vec_ref3 = vec_ref4;
        vec_ref4 = std::move(vec_ref3);

        std::cout << "vec_ref1: moved" << std::endl;
        std::cout << "vec_ref2: moved" << std::endl;
        std::cout << "vec_ref3: moved" << std::endl;
        std::cout << "vec_ref4: a=" << vec_ref4->a_ << ", b=" << vec_ref4->b_ << std::endl;
        std::cout << "vec_ref5: a=" << vec_ref5->a_ << ", b=" << vec_ref5->b_ << std::endl;
        std::cout << "vec_ref6: a=" << vec_ref6->a_ << ", b=" << vec_ref6->b_ << std::endl;
        std::cout << "vec_ref7: a=" << vec_ref7->a_ << ", b=" << vec_ref7->b_ << std::endl;
        std::cout << "vec_ref8: a=" << vec_ref8->a_ << ", b=" << vec_ref8->b_ << std::endl;

        //  hierarchic resource test
        auto movement_ref1 = manager.getResource<TestResource_Movement>("MOVEMENT_1");
    }

    {   //  loading a binary resource
        std::cout << "\n\n[ Test Part " << ++testPart << " ]" << std::endl;
        ResourceManager<ResourceId> manager;

        ResourceInitInfo<Binary> testTXTInfo;
        testTXTInfo.source = ResourceInitInfo<Binary>::FILE;
        testTXTInfo.fileName = "res/test.txt";

        manager.addResourceInfo("TEST_TXT", testTXTInfo);
        ResourcePointer<Binary, ResourceId> testTXT = manager.getResource<Binary>("TEST_TXT");

        unsigned long s = testTXT.get()->getBufferSize();
        char* str = new char[s+1];
        memcpy(str, testTXT.get()->getBufferPtr(), s);
        str[s] = '\0';

        std::cout << str << std::endl;
    }

    {   //  loading a binary resource asynchronously
        std::cout << "\n\n[ Test Part " << ++testPart << " ]" << std::endl;

        ThreadPool pool;
        pool.launchThreads(1);
        ResourceManager<ResourceId> manager(&pool);

        ResourceInitInfo<Binary> testTXTInfo;
        testTXTInfo.source = ResourceInitInfo<Binary>::FILE;
        testTXTInfo.fileName = "res/test.txt";

        manager.addResourceInfo("TEST_TXT", testTXTInfo);
        manager.loadResource("TEST_TXT");
        auto testTXT = manager.getResource<Binary>("TEST_TXT");
        std::cout << "testTXT->status(): " << testTXT->status() << std::endl;
        std::cout << "testTXT->status(): " << testTXT->status() << std::endl;
        std::cout << "testTXT->status(): " << testTXT->status() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        unsigned long s = testTXT.get()->getBufferSize();
        char* str = new char[s+1];
        memcpy(str, testTXT.get()->getBufferPtr(), s);
        str[s] = '\0';

        std::cout << str << std::endl;
    }

    {   //  Vec2f binary tree test
        std::cout << "\n\n[ Test Part " << ++testPart << " ]" << std::endl;

        ThreadPool pool;
        pool.launchThreads(1);
        ResourceManager<ResourceId> manager(&pool);

        ResourceId rootNodeId = makeRecursiveVec2fTreeInfo(manager);

        manager.loadResource(rootNodeId);
        auto root = manager.getResource<TestResource_Vec2fTree>(rootNodeId);
        std::cout << "rootnode ready" << std::endl;

        //std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }

    return 0;
}


#endif // CURRENT_TEST

