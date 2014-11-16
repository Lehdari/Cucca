#ifndef CUCCA_UNITTESTS_UNITTEST4_HPP
#define CUCCA_UNITTESTS_UNITTEST4_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 4


#include "../Core/Resource.hpp"
#include "../Core/ResourcePointer.hpp"

#include <string>


namespace Cucca {

    class TestResource_Vec2f;
    class TestResource_Array;
    class TestResource_Movement;

    template<> struct ResourceInitInfo<TestResource_Vec2f>;
    template<> struct ResourceInitInfo<TestResource_Array>;
    template<> struct ResourceInitInfo<TestResource_Movement>;


    class TestResource_Vec2f : public Resource<TestResource_Vec2f, std::string> {
    public:
        void init(const ResourceInitInfo<TestResource_Vec2f>& initInfo,
                  ResourceManager<std::string>& resourceManager,
                  const std::vector<std::string>& initResources,
                  const std::vector<std::string>& depResources);
        void destroy(void);

    private:
        float a_;
        float b_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Vec2f> : public ResourceInitInfoBase {
        float a;
        float b;
    };

    class TestResource_Array : public Resource<TestResource_Array, std::string> {
    public:
        void init(const ResourceInitInfo<TestResource_Array>& initInfo,
                  ResourceManager<std::string>& resourceManager,
                  const std::vector<std::string>& initResources,
                  const std::vector<std::string>& depResources);
        void destroy(void);

    private:
        int* arr;
    };

    template<>
    struct ResourceInitInfo<TestResource_Array> : public ResourceInitInfoBase {
        unsigned arrSize;
        int first;
        int step;
    };

    //  hierarchical resource example
    class TestResource_Movement : public Resource<TestResource_Movement, std::string> {
    public:
        void init(const ResourceInitInfo<TestResource_Movement>& initInfo,
                  ResourceManager<std::string>& resourceManager,
                  const std::vector<std::string>& initResources,
                  const std::vector<std::string>& depResources);
        void destroy(void);

    private:
        //  child resources
        ResourcePointer<TestResource_Vec2f, std::string> position_;
        ResourcePointer<TestResource_Vec2f, std::string> velocity_;
        ResourcePointer<TestResource_Vec2f, std::string> acceleration_;
    };

    template<>
    struct ResourceInitInfo<TestResource_Movement> : public ResourceInitInfoBase {
        ResourceInitInfo(void) {};
    };

} // namespace Cucca


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST4_HPP
