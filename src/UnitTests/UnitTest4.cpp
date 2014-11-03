#include "../../include/UnitTests/UnitTest4.hpp"


#if CURRENT_TEST == 4


#include "../../include/Core/ResourceManager.hpp"

#include <iostream>


using namespace Cucca;


void TestResource_Vec2f::init(ResourceInitInfo<TestResource_Vec2f>& initInfo,
                              const std::vector<std::string>& initResources,
                              const std::vector<std::string>& depResources) {
    a_ = initInfo.a;
    b_ = initInfo.b;
}

void TestResource_Vec2f::destroy(void) {
    std::cout << "TestResource_Vec2f::destroy" << std::endl;
}


void TestResource_Array::init(ResourceInitInfo<TestResource_Array>& initInfo,
                              const std::vector<std::string>& initResources,
                              const std::vector<std::string>& depResources) {
    arr = new int[initInfo.arrSize];
    arr[0] = initInfo.first;
    for (unsigned i=1; i<initInfo.arrSize; ++i)
        arr[i] = arr[i-1]+initInfo.step;
}

void TestResource_Array::destroy(void) {
    delete[] arr;
    std::cout << "TestResource_Array::destroy" << std::endl;
}


int unitTest(void) {
    ResourceInitInfo<TestResource_Vec2f> initInfo1;
    initInfo1.a = 0.25f;
    initInfo1.b = 0.50f;

    ResourceInitInfo<TestResource_Vec2f> initInfo2;
    initInfo1.a = 0.45f;
    initInfo1.b = 0.20f;

    ResourceManager<std::string> manager;
    manager.addResourceInfo<TestResource_Vec2f>("VEC2F_1", initInfo1, std::vector<std::string>(), std::vector<std::string>());
    manager.addResourceInfo<TestResource_Vec2f>("VEC2F_2", initInfo1, std::vector<std::string>(), std::vector<std::string>());

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

    return 0;
}


#endif // CURRENT_TEST

