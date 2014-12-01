#include "../../include/UnitTests/UnitTest4.hpp"


#if CURRENT_TEST == 4


#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"

#include <iostream>


using namespace Cucca;


void TestResource_Vec2f::init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                              ResourceManager<ResourceId>& resourceManager,
                              const std::vector<ResourceId>& initResources,
                              const std::vector<ResourceId>& depResources) {
    a_ = initInfo.a;
    b_ = initInfo.b;
}

void TestResource_Vec2f::destroy(void) {
    std::cout << "TestResource_Vec2f::destroy" << std::endl;
}


void TestResource_Array::init(const ResourceInitInfo<TestResource_Array>& initInfo,
                              ResourceManager<ResourceId>& resourceManager,
                              const std::vector<ResourceId>& initResources,
                              const std::vector<ResourceId>& depResources) {
    arr = new int[initInfo.arrSize];
    arr[0] = initInfo.first;
    for (unsigned i=1; i<initInfo.arrSize; ++i)
        arr[i] = arr[i-1]+initInfo.step;
}

void TestResource_Array::destroy(void) {
    delete[] arr;
    std::cout << "TestResource_Array::destroy" << std::endl;
}


void TestResource_Movement::init(const ResourceInitInfo<TestResource_Movement>& initInfo,
                                 ResourceManager<ResourceId>& resourceManager,
                                 const std::vector<ResourceId>& initResources,
                                 const std::vector<ResourceId>& depResources) {
    if (depResources.size() < 3)
        throw "TestResource_Movement: unable to initialize resource (insufficient dependency resources provided)"; // TODO_EXCEPTION: throw a proper exception

    position_ = resourceManager.getResource<TestResource_Vec2f>(depResources[0]);
    velocity_ = resourceManager.getResource<TestResource_Vec2f>(depResources[1]);
    acceleration_ = resourceManager.getResource<TestResource_Vec2f>(depResources[2]);
}

void TestResource_Movement::destroy(void) {
    std::cout << "TestResource_Movement::destroy" << std::endl;
}


int unitTest(void) {
    {   //  resource management basics
        ResourceManager<ResourceId> manager;

        ResourceInitInfo<TestResource_Vec2f> vecInitInfo1;
        vecInitInfo1.a = 0.25f;
        vecInitInfo1.b = 0.50f;
        ResourceInitInfo<TestResource_Vec2f> vecInitInfo2;
        vecInitInfo1.a = 0.45f;
        vecInitInfo1.b = 0.20f;
        ResourceInitInfo<TestResource_Vec2f> vecInitInfo3;
        vecInitInfo1.a = -0.8f;
        vecInitInfo1.b = 0.65f;

        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_1", vecInitInfo1, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_2", vecInitInfo2, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_3", vecInitInfo3, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.addResourceInfo<TestResource_Movement>("MOVEMENT_1",
                                                       ResourceInitInfo<TestResource_Movement>(),
                                                       std::vector<ResourceId>(),
                                                       std::vector<ResourceId> {"VEC2F_1", "VEC2F_2", "VEC2F_3"});

        //  hierarchic resource test
        auto movement_ref1 = manager.getResource<TestResource_Movement>("MOVEMENT_1");

        //  some additional RO5 tests
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
    }

    {   //  loading a binary resource
        ResourceManager<ResourceId> manager;

        ResourceInitInfo<Binary> testTXTInfo;
        testTXTInfo.source = ResourceInitInfo<Binary>::FILE;
        testTXTInfo.fileName = "res/test.txt";

        manager.addResourceInfo("TEST_TXT", testTXTInfo, std::vector<ResourceId>(), std::vector<ResourceId>());
        ResourcePointer<Binary, ResourceId> testTXT = manager.getResource<Binary>("TEST_TXT");

        unsigned long s = testTXT.get()->getBufferSize();
        char* str = new char[s+1];
        memcpy(str, testTXT.get()->getBufferPtr(), s);
        str[s] = '\0';

        std::cout << str << std::endl;
    }

    {   //  loading a binary resource asynchronously
        ThreadPool pool;
        pool.launchThreads(1);

        ResourceManager<ResourceId> manager(&pool);

        ResourceInitInfo<Binary> testTXTInfo;
        testTXTInfo.source = ResourceInitInfo<Binary>::FILE;
        testTXTInfo.fileName = "res/test.txt";

        manager.addResourceInfo("TEST_TXT", testTXTInfo, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.loadResource<Binary>("TEST_TXT");

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        ResourcePointer<Binary, ResourceId> testTXT = manager.getResource<Binary>("TEST_TXT");

        unsigned long s = testTXT.get()->getBufferSize();
        char* str = new char[s+1];
        memcpy(str, testTXT.get()->getBufferPtr(), s);
        str[s] = '\0';

        std::cout << str << std::endl;
    }


    return 0;
}


#endif // CURRENT_TEST

