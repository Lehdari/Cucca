/**
    Cucca Game Engine - Core - Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Binary is a resource consisting a buffer of binary data.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#ifndef CUCCA_CORE_BINARY_HPP
#define CUCCA_CORE_BINARY_HPP


#include "Resource.hpp"


namespace Cucca {

    //  Structs and Classes
    class Binary : public Resource<Binary, ResourceId> {
    public:
        Binary(void);
        ~Binary(void);

        //  Resource init and destroy member functions
        void init(const ResourceInitInfo<Binary>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        char* getBufferPtr(void);
        unsigned long getBufferSize(void);

    private:
        char* buffer_;
        unsigned long size_;
    };


    template<> struct ResourceInitInfo<Binary> : public ResourceInitInfoBase {
        enum Source {
            SOURCE_FILE
        } source;

        std::string fileName;
    };

} // namespace Cucca


#endif // CUCCA_CORE_BINARY_HPP
