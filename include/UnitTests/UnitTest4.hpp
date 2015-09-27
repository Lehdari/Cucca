#ifndef CUCCA_UNITTESTS_UNITTEST4_HPP
#define CUCCA_UNITTESTS_UNITTEST4_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 4


#include <Cucca/Core/Resource.hpp>
#include <Cucca/Core/ResourcePointer.hpp>


namespace Cucca {

    class TestResource_Vec2f;
    class TestResource_Movement;
    class TestResource_Vec2fTree;

    template<> struct ResourceInitInfo<TestResource_Vec2f>;
    template<> struct ResourceInitInfo<TestResource_Movement>;
    template<> struct ResourceInitInfo<TestResource_Vec2fTree>;


    class TestResource_Vec2f : public Resource<TestResource_Vec2f, ResourceId> {
    public:
        TestResource_Vec2f(void) {}
        ~TestResource_Vec2f(void);

        void init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        float a_;
        float b_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Vec2f> : public ResourceInitInfoBase {
        float a, b;
    };

    //  hierarchical resource example
    class TestResource_Movement : public Resource<TestResource_Movement, ResourceId> {
    public:
        TestResource_Movement(void) {}
        ~TestResource_Movement(void);

        void init(const ResourceInitInfo<TestResource_Movement>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

    private:
        ResourcePointer<TestResource_Vec2f, ResourceId> position_;
        ResourcePointer<TestResource_Vec2f, ResourceId> velocity_;
        ResourcePointer<TestResource_Vec2f, ResourceId> acceleration_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Movement> : public ResourceInitInfoBase {
        //ResourceInitInfo(void) {};
    };

    class TestResource_Vec2fTree : public Resource<TestResource_Vec2fTree, ResourceId> {
    public:
        TestResource_Vec2fTree(void) {}
        ~TestResource_Vec2fTree(void);

        void init(const ResourceInitInfo<TestResource_Vec2fTree>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

    private:
        ResourcePointer<TestResource_Vec2fTree, ResourceId> leftNode_;
        ResourcePointer<TestResource_Vec2fTree, ResourceId> rightNode_;
        ResourcePointer<TestResource_Vec2f, ResourceId> data_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Vec2fTree> : public ResourceInitInfoBase {
        //ResourceId leftNode;
        //ResourceId rightNode;
        //ResourceId data;
    };

} // namespace Cucca

Cucca::ResourceId makeRecursiveVec2fTreeInfo(Cucca::ResourceManager<Cucca::ResourceId>& resourceManager,
                                             unsigned* nodeId = nullptr,
                                             unsigned* vec2fId = nullptr,
                                             unsigned layer = 0);

int unitTest(void);



#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST4_HPP
