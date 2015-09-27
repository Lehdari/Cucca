/**
    Cucca Game Engine - Core - Binary.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-02-03
**/


#include <Cucca/Core/Binary.hpp>


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

char* Binary::getBufferPtr(void) {
    return buffer_;
}

unsigned long Binary::getBufferSize(void) {
    return size_;
}
