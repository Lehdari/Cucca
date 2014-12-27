/**
    Cucca Game Engine - Core - Binary.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#include "../../include/Core/Binary.hpp"


#include <cstdio>


using namespace Cucca;


Binary::Binary(void) :
    buffer_(nullptr),
    size_(0)
{}

Binary::~Binary(void) {
    if (buffer_)
        delete[] buffer_;
}

void Binary::init(const ResourceInitInfo<Binary>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager) {
    switch (initInfo.source) {
    case ResourceInitInfo<Binary>::SOURCE_FILE:
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

            buffer_ = new char[size_ + 1]; // TODO_ALLOCATOR
            fread(buffer_, sizeof(char), size_, file);
            buffer_[size_] = '\0';

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
