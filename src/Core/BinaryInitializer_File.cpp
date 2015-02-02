/**
    Cucca Game Engine - Core - BinaryInitializer_File.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-01
**/


#include "../../include/Core/BinaryInitializer_File.hpp"


#include <cstdio>


using namespace Cucca;


BinaryInitializer_File::BinaryInitializer_File(const std::string& fileName) :
    fileName_(fileName)
{}

void BinaryInitializer_File::init(Binary& resource,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager) {
    FILE* file = fopen(fileName_.c_str(), "rb");
    if (file) {
        if (fseek(file, 0, SEEK_END)) {
            fclose(file);
            throw "Binary: error seeking end of file"; // TODO_EXCEPTION: throw a proper exception
        }

        resource.size_ = ftell(file);

        if (fseek(file, 0, SEEK_SET)) {
            fclose(file);
            throw "Binary: error seeking beginning of file"; // TODO_EXCEPTION: throw a proper exception
        }

        resource.buffer_ = new char[resource.size_ + 1]; // TODO_ALLOCATOR
        fread(resource.buffer_, sizeof(char), resource.size_, file);
        resource.buffer_[resource.size_] = '\0';

        fclose(file);
    }
    else
        throw "Binary: unable to open file " + fileName_; // TODO_EXCEPTION: throw a proper exception
}

void BinaryInitializer_File::destroy(Binary& resource) {
    if (resource.buffer_) {
        delete[] resource.buffer_;
        resource.buffer_ = nullptr;
        resource.size_ = 0;
    }
}
