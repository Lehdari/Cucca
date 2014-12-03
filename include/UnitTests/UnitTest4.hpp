#ifndef CUCCA_UNITTESTS_UNITTEST4_HPP
#define CUCCA_UNITTESTS_UNITTEST4_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 4


#include "../Core/Resource.hpp"
#include "../Core/ResourcePointer.hpp"


namespace Cucca {

    class TestResource_Vec2f;
    class TestResource_Array;
    class TestResource_Movement;

    template<> struct ResourceInitInfo<TestResource_Vec2f>;
    template<> struct ResourceInitInfo<TestResource_Array>;
    template<> struct ResourceInitInfo<TestResource_Movement>;


    class TestResource_Vec2f : public Resource<TestResource_Vec2f, ResourceId> {
    public:
        ~TestResource_Vec2f(void);

        void init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                  ResourceManager<ResourceId>& resourceManager,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources);
        void destroy(void);

        float a_;
        float b_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Vec2f> : public ResourceInitInfoBase {
        float a, b;
    };

    class TestResource_Array : public Resource<TestResource_Array, ResourceId> {
    public:
        ~TestResource_Array(void);

        void init(const ResourceInitInfo<TestResource_Array>& initInfo,
                  ResourceManager<ResourceId>& resourceManager,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources);
        void destroy(void);

        int* arr_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Array> : public ResourceInitInfoBase {
        unsigned arrSize;
        int first;
        int step;
    };

    //  hierarchical resource example
    class TestResource_Movement : public Resource<TestResource_Movement, ResourceId> {
    public:
        ~TestResource_Movement(void);

        void init(const ResourceInitInfo<TestResource_Movement>& initInfo,
                  ResourceManager<ResourceId>& resourceManager,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources);
        void destroy(void);

        ResourcePointer<TestResource_Vec2f, ResourceId> position_;
        ResourcePointer<TestResource_Vec2f, ResourceId> velocity_;
        ResourcePointer<TestResource_Vec2f, ResourceId> acceleration_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Movement> : public ResourceInitInfoBase {
        ResourceInitInfo(void) {};
    };

} // namespace Cucca


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST4_HPP
