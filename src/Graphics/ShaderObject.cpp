/**
    Cucca Game Engine - Graphics - ShaderObject.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#include <Cucca/Graphics/ShaderObject.hpp>


using namespace Cucca;


ShaderObject::ShaderObject(void) :
    objectId_(0)
{}

GLuint ShaderObject::getId(void) const {
    return objectId_;
}
