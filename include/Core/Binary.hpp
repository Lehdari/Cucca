/**
    Cucca Game Engine - Core - Resource.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Binary is a resource consisting a buffer of binary data.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-17
**/


#ifndef CUCCA_CORE_BINARY_HPP
#define CUCCA_CORE_BINARY_HPP


#include "Resource.hpp"

#include <memory>
#include <cstdio>


namespace Cucca {

    //  Structs and Classes
    class Binary : public Resource<Binary, ResourceId> {
    public:
        Binary(void);

        /*Binary(ResourceBase&& other) :
            Resource<Binary, ResourceId>(std::move(other))
        {}*/

        ~Binary(void);

        //  Resource init and destroy member functions
        void init(const ResourceInitInfo<Binary>& initInfo,
                  ResourceManager<ResourceId>& resourceManager,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources);
        void destroy(void);

        char* getBufferPtr(void);
        unsigned long getBufferSize(void);

    private:
        char* buffer_;
        unsigned long size_;
    };


    template<> struct ResourceInitInfo<Binary> : public ResourceInitInfoBase {
        enum Source {
            FILE
        } source;

        std::string fileName;
    };


    //  Member Definitions
    Binary::Binary(void) :
        buffer_(nullptr),
        size_(0)
    {}

    Binary::~Binary(void) {
        if (buffer_)
            delete[] buffer_;
    }

    void Binary::init(const ResourceInitInfo<Binary>& initInfo,
                      ResourceManager<ResourceId>& resourceManager,
                      const std::vector<ResourceId>& initResources,
                      const std::vector<ResourceId>& depResources) {
        switch (initInfo.source) {
        case ResourceInitInfo<Binary>::FILE:
            FILE* file = fopen(initInfo.fileName.c_str(), "rb");
            if (file) {
                if (fseek(file, 0, SEEK_END)) {
                    fclose(file);
                    throw "Binary: error seeking end of file"; // TODO_EXCEPTION: throw a proper exception
                }

                size_ = ftell(file);

                if (fseek(file, 0, SEEK_SET)) {
                    fclose(file);
                    throw "Binary: error seeking beginning of file"; // TODO_EXCEPTION: throw a proper exception
                }

                buffer_ = new char[size_]; // TODO_ALLOCATOR
                fread(buffer_, sizeof(char), size_, file);

                fclose(file);
            }
            else
                throw "Binary: unable to open file " + initInfo.fileName; // TODO_EXCEPTION: throw a proper exception
        break;
        }
    }

    void Binary::destroy(void) {
        if (buffer_) {
            delete[] buffer_;
            buffer_ = nullptr;
            size_ = 0;
        }
    }

    char* Binary::getBufferPtr(void) {
        return buffer_;
    }

    unsigned long Binary::getBufferSize(void) {
        return size_;
    }

} // namespace Cucca


#endif // CUCCA_CORE_BINARY_HPP
