#ifndef CUCCA_UNITTESTS_UNITTEST4_HPP
#define CUCCA_UNITTESTS_UNITTEST4_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 4


#include "../Core/Resource.hpp"

#include <string>


namespace Cucca {

    class TestResource_Vec2f;
    class TestResource_Array;

    template<> struct ResourceInitInfo<TestResource_Vec2f>;
    template<> struct ResourceInitInfo<TestResource_Array>;


    class TestResource_Vec2f : public Resource<TestResource_Vec2f, std::string> {
    public:
        void init(ResourceInitInfo<TestResource_Vec2f>& initInfo,
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
        void init(ResourceInitInfo<TestResource_Array>& initInfo,
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

} // namespace Cucca


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST4_HPP
