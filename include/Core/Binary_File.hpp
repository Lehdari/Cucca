/**
    Cucca Game Engine - Core - Binary_File.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    This file specifies BinaryInitInfoFile class and Binary init
    and destroy member function template specializations for
    initializing Binary resources from external files.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-03
**/


#ifndef CUCCA_CORE_BINARY_FILE_HPP
#define CUCCA_CORE_BINARY_FILE_HPP


#include "Binary.hpp"


namespace Cucca {

    //  Structs and classes
    struct BinaryInitInfoFile : public ResourceInitInfoBase {
        std::string fileName;
    };


    //  Template specializations
    template<>
    void Binary::init<BinaryInitInfoFile>(const BinaryInitInfoFile& initInfo,
                                          const std::vector<ResourceId>& initResources,
                                          const std::vector<ResourceId>& depResources,
                                          ResourceManager<ResourceId>* resourceManager) {
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
    }

    template<>
    void Binary::destroy<BinaryInitInfoFile>(void) {
        if (buffer_) {
            delete[] buffer_;
            buffer_ = nullptr;
            size_ = 0;
        }
    }

};


#endif // CUCCA_CORE_BINARY_FILE_HPP
