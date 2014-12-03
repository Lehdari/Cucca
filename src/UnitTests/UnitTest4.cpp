#include "../../include/UnitTests/UnitTest4.hpp"


#if CURRENT_TEST == 4


#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"

#include <iostream>


using namespace Cucca;


TestResource_Vec2f::~TestResource_Vec2f(void) {
    std::cout << "~TestResource_Vec2f" << std::endl;
}

void TestResource_Vec2f::init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                              ResourceManager<ResourceId>& resourceManager,
                              const std::vector<ResourceId>& initResources,
                              const std::vector<ResourceId>& depResources) {
    std::cout << "TestResource_Vec2f::init" << std::endl;
    std::cout << "  initInfo.a=" << initInfo.a << std::endl;
    std::cout << "  initInfo.b=" << initInfo.b << std::endl;
    a_ = initInfo.a;
    b_ = initInfo.b;
}

void TestResource_Vec2f::destroy(void) {
    std::cout << "TestResource_Vec2f::destroy" << std::endl;
}

TestResource_Array::~TestResource_Array(void) {
    std::cout << "~TestResource_Array" << std::endl;
}

void TestResource_Array::init(const ResourceInitInfo<TestResource_Array>& initInfo,
                              ResourceManager<ResourceId>& resourceManager,
                              const std::vector<ResourceId>& initResources,
                              const std::vector<ResourceId>& depResources) {
    std::cout << "TestResource_Array::init" << std::endl;
    arr_ = new int[initInfo.arrSize];
    arr_[0] = initInfo.first;
    for (unsigned i=1; i<initInfo.arrSize; ++i)
        arr_[i] = arr_[i-1]+initInfo.step;
}

void TestResource_Array::destroy(void) {
    delete[] arr_;
    std::cout << "TestResource_Array::destroy" << std::endl;
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


int unitTest(void) {
    auto testPart = 0u;

    {   //  resource management basics
        std::cout << "[ Test Part " << ++testPart << " ]" << std::endl;
        ResourceManager<ResourceId> manager;

        ResourceInitInfo<TestResource_Vec2f> vecInitInfo1;
        vecInitInfo1.a = 0.25f;
        vecInitInfo1.b = 0.50f;
        ResourceInitInfo<TestResource_Vec2f> vecInitInfo2;
        vecInitInfo2.a = -0.45f;
        vecInitInfo2.b = -0.20f;
        ResourceInitInfo<TestResource_Vec2f> vecInitInfo3;
        vecInitInfo3.a = -0.7f;
        vecInitInfo3.b = 0.65f;

        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_1", vecInitInfo1, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_2", vecInitInfo2, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.addResourceInfo<TestResource_Vec2f>("VEC2F_3", vecInitInfo3, std::vector<ResourceId>(), std::vector<ResourceId>());
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

        manager.addResourceInfo("TEST_TXT", testTXTInfo, std::vector<ResourceId>(), std::vector<ResourceId>());
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

        manager.addResourceInfo("TEST_TXT", testTXTInfo, std::vector<ResourceId>(), std::vector<ResourceId>());
        manager.loadResource<Binary>("TEST_TXT");
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

    return 0;
}


#endif // CURRENT_TEST

