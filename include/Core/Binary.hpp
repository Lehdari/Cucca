/**
    Cucca Game Engine - Core - Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Binary is a resource consisting a buffer of binary data.
    Buffer is null/terminated, thus it can be used as a C string.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#ifndef CUCCA_CORE_BINARY_HPP
#define CUCCA_CORE_BINARY_HPP


#include "Resource.hpp"


namespace Cucca {

    //  Structs and Classes
    CUCCA_RESOURCE(Binary) {
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


    CUCCA_RESOURCE_INIT_INFO(Binary) {
        enum Source {
            SOURCE_FILE
        } source;

        std::string fileName;
    };

} // namespace Cucca


#endif // CUCCA_CORE_BINARY_HPP
