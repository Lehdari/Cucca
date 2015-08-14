/**
    Cucca Game Engine - Core - Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Binary is a resource consisting a buffer of binary data.
    Buffer is null/terminated, thus it can be used as a C string.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-03
**/


#ifndef CUCCA_CORE_BINARY_HPP
#define CUCCA_CORE_BINARY_HPP


#include "Resource.hpp"


namespace Cucca {

    //  Structs and Classes
    CUCCA_RESOURCE(Binary) {
    public:
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        Binary(void);
        ~Binary(void);

        char* getBufferPtr(void);
        unsigned long getBufferSize(void);

    private:
        char* buffer_;
        unsigned long size_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_BINARY_HPP
